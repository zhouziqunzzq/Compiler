#include<bits/stdc++.h>
#include "ASMGenerator.h"

using namespace std;

ASMGenerator::ASMGenerator(QuadrupleTable *qt, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
                           StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
                           SymbolTable *st, TypeTable *tt, Vall *vall) :
        kt(kt), dt(dt), cct(cct),
        strct(strct), ict(ict), fct(fct), st(st),
        tt(tt), vall(vall), qt(qt) {
    fillActiveInfo();
    rdl = -1;
    rdlActive = false;
    opcode[0] = "ADD";
    opcode[1] = "MIN";
    opcode[2] = "MUL";
    opcode[3] = "DIV";
}

void ASMGenerator::fillActiveInfo() {
    vector<SymbolTableRecord> &t = st->getTable();
    for (auto &it : t) {
        if (it.isUsed || (!it.isUsed && it.cat
                                        == V && it.addr != -1)) {
            it.isActive = !it.isTemp;
        }
    }
    for (auto it = qt->rbegin(); it != qt->rend(); ++it) {
        it->isActiveR = t[it->rst].isActive;
        t[it->rst].isActive = false;
        it->isActive1 = t[it->opr1].isActive;
        t[it->opr1].isActive = true;
        if (it->opr2 != -1) {
            it->isActive2 = t[it->opr2].isActive;
            t[it->opr2].isActive = true;
        }
    }
}

void ASMGenerator::genHeader() {
    int cnt = 0;
    obj.emplace_back("DSEG\tSEGMENT");
    for (auto it = vall->v.begin(); it != vall->v.end(); ++it) {
        obj.push_back("DATA" + numToString<int>(cnt++) + "\tDB\t0");
    }
    obj.emplace_back("DSEG\tENDS");

    obj.emplace_back("SSEG\tSEGMENT\tSTACK");
    obj.emplace_back("SKTOP\tDB\t100 DUP(0)");
    obj.emplace_back("SSEG\tENDS");

    obj.emplace_back("CSEG\tSEGMENT");
    obj.emplace_back("\tASSUME\tCS:CSEG, DS:DSEG");
    obj.emplace_back("\tASSUME\tSS:SSEG");
    obj.emplace_back("START:\tMOV\tAX, DSEG");
    obj.emplace_back("\tMOV\tDS, AX");
    obj.emplace_back("\tMOV\tAX, SSEG");
    obj.emplace_back("\tMOV\tSS, AX");
    obj.emplace_back("\tMOV\tSP, LENGTH SKTOP");
}

void ASMGenerator::genMOV(int id) {
    char buff[1000];
    vector<SymbolTableRecord> t = st->getTable();
    if (t[id].cat == V) {
        sprintf(buff, "\tMOV\tAX, [%04x]", t[id].addr);
        obj.emplace_back(buff);
    } else if (tt->getValue(t[id].type).tval == INTEGER) {
        sprintf(buff, "\tMOV\tAX, %d", ict->getValue(t[id].addr));
        obj.emplace_back(buff);
    } else {
        sprintf(buff, "\tMOV\tAX, %f", fct->getValue(t[id].addr));
        obj.emplace_back(buff);
    }
}

void ASMGenerator::genST(int id) {
    char buff[1000];
    vector<SymbolTableRecord> t = st->getTable();
    if (t[id].cat == V) {
        sprintf(buff, "\tMOV\t[%04x], AX", t[id].addr);
        obj.emplace_back(buff);
    }
}

void ASMGenerator::genOP(int op, int id) {
    char buff[1000];
    vector<SymbolTableRecord> t = st->getTable();
    if (t[id].cat == V) {
        sprintf(buff, "\t%s\tAX, [%04x]", opcode[op].c_str(), t[id].addr);
        obj.emplace_back(buff);
    } else if (tt->getValue(t[id].type).tval == INTEGER) {
        sprintf(buff, "\t%s\tAX, %d", opcode[op].c_str(), ict->getValue(t[id].addr));
        obj.emplace_back(buff);
    } else {
        sprintf(buff, "\t%s\tAX, %f", opcode[op].c_str(), fct->getValue(t[id].addr));
        obj.emplace_back(buff);
    }
}

void ASMGenerator::genBody() {
    for (auto &it : *qt) {
        if (it.op != ASSIGN) {
            if (rdl == -1) {
                genMOV(it.opr1);
                genOP(it.op, it.opr2);
            } else if (rdl == it.opr1) {
                if (it.isActive1) {
                    genST(it.opr1);
                }
                genOP(it.op, it.opr2);
            } else if (rdl == it.opr2 && (it.op == ADD || it.op == MUL)) {
                if (it.isActive2) {
                    genST(it.opr2);
                }
                genOP(it.op, it.opr1);
            } else {
                if (rdlActive) {
                    genST(rdl);
                }
                genMOV(it.opr1);
                genOP(it.op, it.opr2);
            }
            // Update rdl and rdlActive
            rdl = it.rst;
            rdlActive = it.isActiveR;
        } else    //ASSIGN
        {
            if (rdl == -1) {
                genMOV(it.opr1);
            } else if (rdl == it.opr1) {
                if (it.isActive1) {
                    genST(it.opr1);
                }
            } else {
                if (rdlActive) {
                    genST(rdl);
                }
                genMOV(it.opr1);
            }
            // Update rdl and rdlActive
            rdl = it.rst;
            rdlActive = it.isActiveR;
        }
    }
    // Store rdl if needed
    if (rdlActive) {
        genST(rdl);
    }
}

void ASMGenerator::genFooter() {
    obj.emplace_back("\tMOV\tAH, 4CH");
    obj.emplace_back("\tINT\t21H");
    obj.emplace_back("CSEG\tENDS");
    obj.emplace_back("\tEND\tSTART");
}

string ASMGenerator::gen() {
    genHeader();
    genBody();
    genFooter();
    string buff;
    for (auto &it : obj)
        buff += it + "\n";
    return buff;
}
