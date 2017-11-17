#include<bits/stdc++.h>
#include "OPAnalyzer.h"
#include "utils.h"
#define isVN(t) v_cat.find(getWord((t))) == v_cat.end()
#define isVT(t) v_cat.find(getWord((t))) != v_cat.end()
#define TMPPREFIX "tmp"

using namespace std;

OPAnalyzer::OPAnalyzer(Scanner *sc, stack<Token> *sem, QuadrupleTable *qt) : sc(sc), sem(sem), qt(qt), tmpCnt(0)
{
    init_mp();
    init_g();
    init_vcat();
}

void OPAnalyzer::init_mp()
{
    mp["+"]["+"] = '>';
    mp["+"]["-"] = '>';
    mp["+"]["*"] = '<';
    mp["+"]["/"] = '<';
    mp["+"]["("] = '<';
    mp["+"][")"] = '>';
    mp["+"]["id"] = '<';
    mp["+"]["c"] = '<';

    mp["-"]["+"] = '>';
    mp["-"]["-"] = '>';
    mp["-"]["*"] = '<';
    mp["-"]["/"] = '<';
    mp["-"]["("] = '<';
    mp["-"][")"] = '>';
    mp["-"]["id"] = '<';
    mp["-"]["c"] = '<';

    mp["*"]["+"] = '>';
    mp["*"]["-"] = '>';
    mp["*"]["*"] = '>';
    mp["*"]["/"] = '>';
    mp["*"]["("] = '<';
    mp["*"][")"] = '>';
    mp["*"]["id"] = '<';
    mp["*"]["c"] = '<';

    mp["/"]["+"] = '>';
    mp["/"]["-"] = '>';
    mp["/"]["*"] = '>';
    mp["/"]["/"] = '>';
    mp["/"]["("] = '<';
    mp["/"][")"] = '>';
    mp["/"]["id"] = '<';
    mp["/"]["c"] = '<';

    mp["("]["+"] = '<';
    mp["("]["-"] = '<';
    mp["("]["*"] = '<';
    mp["("]["/"] = '<';
    mp["("]["("] = '<';
    mp["("][")"] = '=';
    mp["("]["id"] = '<';
    mp["("]["c"] = '<';

    mp[")"]["+"] = '>';
    mp[")"]["-"] = '>';
    mp[")"]["*"] = '>';
    mp[")"]["/"] = '>';
    mp[")"][")"] = '>';

    mp["id"]["+"] = '>';
    mp["id"]["-"] = '>';
    mp["id"]["*"] = '>';
    mp["id"]["/"] = '>';
    mp["id"][")"] = '>';

    mp["c"]["+"] = '>';
    mp["c"]["-"] = '>';
    mp["c"]["*"] = '>';
    mp["c"]["/"] = '>';
    mp["c"][")"] = '>';
}

void OPAnalyzer::init_g()
{
    g["E+T"] = "E";
    g["E-T"] = "E";
    g["T"] = "E";
    g["T*F"] = "T";
    g["T/F"] = "T";
    g["F"] = "T";
    g["GF"] = "F";
    g["(E)"] = "F";
    g["id"] = "GF";
    g["c"] = "GF";
}

void OPAnalyzer::init_vcat()
{
    v_cat["+"] = true;
    v_cat["-"] = true;
    v_cat["*"] = true;
    v_cat["/"] = true;
    v_cat["("] = true;
    v_cat[")"] = true;
    v_cat["id"] = true;
    v_cat["c"] = true;
}

bool OPAnalyzer::isEnd(string s)
{
    if (s == "+" || s == "-" || s == "*" || s == "/" ||
            s == "(" || s == ")" || s == "id" || s == "c" ||
            s == "E" || s == "T" || s == "F" || s == "GF")
        return false;
    else
        return true;
}

string OPAnalyzer::getWord(Token tmp)
{
    string res;
    if(tmp.type == IDENTIFIER)
        res = "id";
    else if((tmp.type==CHARCONST) || (tmp.type==STRCONST) || (tmp.type==INTCONST) || (tmp.type==FLOATCONST))
        res = "c";
    else res = tmp.word;
    return res;
}

string OPAnalyzer::getS(Token &t1, Token &lastToken)
{
    Token tmp;
    Token tmptst = t1;
    string res;
    while(!tst.empty() && mp[getWord(tst.top())][getWord(tmptst)] != '<')
    {
        tmp = st.top();
        res = getWord(tmp) + res;
        if (isVT(tmp) && tmp == tst.top())
        {
            tmptst = tst.top();
            tst.pop();
        }
        st.pop();
        if(st.empty()) break;
    }
    // Pop out remaining VN in st
    while (!st.empty() && (isVN(st.top()) ||
                           getWord(st.top()) != getWord(tst.top())))
    {
        res = getWord(st.top()) + res;
        st.pop();
    }
    lastToken = tmp;
    return res;
}

string OPAnalyzer::getTmpName()
{
    SymbolTableRecord str;
    do
    {
        str.name = TMPPREFIX + numToString<int>(tmpCnt++);
    }
    while (sc->st->has(str));
    return str.name;
}

bool OPAnalyzer::GEQ(char op)
{
    bool flag = true;
    Operation ope;
    if(op == '+')
        ope = ADD;
    if(op == '-')
        ope = MINUS;
    if(op == '*')
        ope = MUL;
    if(op == '/')
        ope = DIV;
    int opr1, opr2;
    opr2 = sem->top().id;
    sem->pop();
    opr1 = sem->top().id;
    sem->pop();
    Tval t1, t2;
    t1 = getTval(opr1);
    t2 = getTval(opr2);
    TypeTableRecord ttr;
    if(t1 == FLOAT)
    {
        if((t2 == INTEGER) || (t2 == FLOAT))
            ttr.tval = FLOAT;
        else flag = false;
    }
    else if(t2 == FLOAT)
    {
        if((t1 == INTEGER) || (t1 == FLOAT))
            ttr.tval = FLOAT;
        else flag = false;
    }
    else if((t1 == INTEGER) && (t2 == INTEGER))
        ttr.tval = INTEGER;
    else flag = false;
    if(flag == false) return flag;
    string tname = getTmpName();
    Category tc = (getCat(opr1) == C && getCat(opr2)) == C ? C : V;
    int rst = sc->st->entry(tname, sc->tt->getID(ttr), tc, -1);
    Token t(IDENTIFIER, tname, rst);
    sem->push(t);
    Quadruple q(ope, opr1, opr2, rst);
    qt->push_back(q);
    return flag;
}

bool OPAnalyzer::CALC(char op)
{
    Operation ope;
    if(op == '+')
        ope = ADD;
    if(op == '-')
        ope = MINUS;
    if(op == '*')
        ope = MUL;
    if(op == '/')
        ope = DIV;
    int opr1, opr2;
    opr2 = sem->top().id;
    sem->pop();
    opr1 = sem->top().id;
    sem->pop();
    if (sc->st->getValue(opr1).cat != C ||
            sc->st->getValue(opr2).cat != C)    // not a const expression
        return false;
    Tval t1, t2;
    t1 = getTval(opr1);
    t2 = getTval(opr2);
    TypeTableRecord ttr;
    if(t1 == FLOAT)
    {
        if((t2 == INTEGER) || (t2 == FLOAT))
            ttr.tval = FLOAT;
        else return false;
    }
    else if(t2 == FLOAT)
    {
        if((t1 == INTEGER) || (t1 == FLOAT))
            ttr.tval = FLOAT;
        else return false;
    }
    else if((t1 == INTEGER) && (t2 == INTEGER))
        ttr.tval = INTEGER;
    else return false;
    int rst;
    if (ttr.tval == INTEGER)
    {
        int i = calcConstResult(ope, getIntVal(opr1), getIntVal(opr2));
        int iaddr = sc->ict->entry(i);
        rst = sc->st->entry(numToString<int>(i), sc->tt->getID(ttr), C, iaddr);
        Token t(INTCONST, numToString<int>(i), rst);
        sem->push(t);
    }
    else if (ttr.tval == FLOAT)
    {
        float i;
        if (t1 == FLOAT && t2 == FLOAT)
            i = calcConstResult(ope, getFloatVal(opr1), getFloatVal(opr2));
        else if (t1 == INTEGER)
            i = calcConstResult(ope, getIntVal(opr1), getFloatVal(opr2));
        else
            i = calcConstResult(ope, getFloatVal(opr1), getIntVal(opr2));
        int iaddr = sc->fct->entry(i);
        rst = sc->st->entry(numToString<float>(i), sc->tt->getID(ttr), C, iaddr);
        Token t(FLOATCONST, numToString<float>(i), rst);
        sem->push(t);
    }
    else return false;
    return true;
}

bool OPAnalyzer::E(bool isConstDef)
{
    while (!st.empty())
        st.pop();
    while (!tst.empty())
        tst.pop();
    // st: Analyze stack
    // tst: Analyze stack with only VT in it
    // flag: The result of OPAnalyzation
    // f2: Whether Scanner reaches the end of an Expression
    bool flag = true, f2 = false;
    // t1: Current token to be analyzed given by Scanner
    Token t1 = sc->getLastToken();
    // t2: The top of st
    Token t2;
    // vst: The top of tst
    Token vst;
    // Initialize st, tst, t1
    if (isEnd(getWord(t1)))  // Special judge for empty expression
        return false;
    printf("Pushing %s into st and moving on...\n", getWord(t1).c_str());
    st.push(t1);
    if (isVT(t1))
        tst.push(t1);
    sc->next();
    t1 = sc->getLastToken();
    while(true)
    {
        t2 = st.top();
        if(!f2 && isEnd(getWord(t1)))
            f2 = true;
        map<string, map<string, char> >::iterator it2;
        map<string, char>::iterator it1;
        if (!tst.empty())
        {
            vst = tst.top();
            it2 = mp.find(getWord(vst));
        }
        if (tst.empty() || it2 != mp.end())
        {
            if (!tst.empty())
            {
                it1 = mp[getWord(vst)].find(getWord(t1));
            }
            if (f2 || tst.empty() || it1 != mp[getWord(vst)].end())
            {
                if(f2 || (!tst.empty() && mp[getWord(vst)][getWord(t1)] == '>'))
                {
                    printf("Performing reduction...\n");
                    Token lastToken;
                    string stmp = getS(t1, lastToken);
                    printf("stmp: %s\n", stmp.c_str());
                    auto ts = g.find(stmp);
                    if(ts != g.end())
                    {
                        if (!isConstDef)
                        {
                            if(stmp.find("+") != string::npos) flag = GEQ('+');
                            if(stmp.find("-") != string::npos) flag = GEQ('-');
                            if(stmp.find("*") != string::npos) flag = GEQ('*');
                            if(stmp.find("/") != string::npos) flag = GEQ('/');
                            if(flag == false) break;
                        }
                        else
                        {
                            if(stmp.find("+") != string::npos) flag = CALC('+');
                            if(stmp.find("-") != string::npos) flag = CALC('-');
                            if(stmp.find("*") != string::npos) flag = CALC('*');
                            if(stmp.find("/") != string::npos) flag = CALC('/');
                            if(flag == false) break;
                        }

                        if((stmp == "id") || (stmp == "c"))
                        {
                            sem->push(lastToken);
                        }

                        Token to(KEYWORD, g[stmp], -1);
                        printf("g[stmp]: %s\n", g[stmp].c_str());
                        st.push(to);
                    }
                    else flag = false;
                }
                else
                {
                    printf("Pushing %s into st and moving on...\n", getWord(t1).c_str());
                    st.push(t1);
                    if (isVT(t1))
                        tst.push(t1);
                    sc->next();
                    t1 = sc->getLastToken();
                }
            }
            else
                flag = false;
        }
        else
            flag = false;
        if(flag == false) break;
        if(st.empty()) break;
        if(f2 && st.size() == 1)
        {
            Token tt=st.top();
            printf("getWord(tt): %s\n", getWord(tt).c_str());
            if (isVN(tt))
            {
                flag = true;
                break;
            }
        }
    }
    printf("OPAnalyzer::flag = %d\n", flag);
    return flag;
}
