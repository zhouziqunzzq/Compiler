#include<bits/stdc++.h>
#include "DAGOptimizer.h"
#include "Quadruple.h"
#include "QuadrupleTable.h"
#include "Category.h"
#define getTvalDAG(x) tt->getValue(st->getValue((x)).type).tval
#define getIntValDAG(x) ict->getValue(st->getValue((x)).addr)
#define getFloatValDAG(t) fct->getValue(st->getValue((t)).addr)
#define isInteger(x) getTvalDAG(x) == INTEGER
#define isFloat(x) getTvalDAG(x) == FLOAT
#define getIntConst(x) ict->getValue(st->getValue(nodes[vCache[(x)].back()].priTag).addr)
#define getFloatConst(x) fct->getValue(st->getValue(nodes[vCache[(x)].back()].priTag).addr)
using namespace std;

DAGOptimizer::DAGOptimizer(QuadrupleTable *qt, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
            StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
            SymbolTable *st, TypeTable *tt, Vall *vall) : kt(kt), dt(dt), cct(cct),
        strct(strct), ict(ict), fct(fct), st(st), tt(tt), vall(vall), qt(qt)
{
    buildDAG();
}

void DAGOptimizer::print()
{
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        printf("#########################\n");
        printf("id: %d\n", it->id);
        printf("priTag: %s\n", st->getValue(it->priTag).name.c_str());
        printf("secTag(%d): ", it->secTag.size());
        for (auto iit = it->secTag.begin(); iit != it->secTag.end(); ++iit)
        {
            printf("%s ", st->getValue(*iit).name.c_str());
        }
        printf("\n");
        printf("op: %d\n", it->op);
        if (it->pl != -1)
            printf("pl.id: %d\n", it->pl);
        if (it->pr != -1)
            printf("pr.id: %d\n", it->pr);
    }
}

int DAGOptimizer::insertNode(int tokenID)
{
    if (tokenID < 0)
        return tokenID;
    else if (vCache.find(tokenID) != vCache.end())
    {
        return vCache[tokenID].back();
    }
    else
    {
        cout << "Insert " << st->getValue(tokenID).name << endl;
        DAGNode n;
        n.id = nodes.size();
        n.priTag = tokenID;
        vCache[tokenID].push_back(n.id);
        nodes.push_back(n);
        return n.id;
    }
}

void DAGOptimizer::removeTag(int tokenID)
{
    if (vCache.find(tokenID) != vCache.end())
    {
        printf("Remove tag %s\n", st->getValue(tokenID).name.c_str());
        int nodeID;
        for (auto rit = vCache[tokenID].begin();
            rit != vCache[tokenID].end(); ++rit)
        {
            nodeID = *rit;
            cout << "nodeID: " << nodeID << endl;
            if (tokenID != nodes[nodeID].priTag)
            {
                for (auto it = nodes[nodeID].secTag.begin();
                    it != nodes[nodeID].secTag.end(); ++it)
                {
                    if (*it == tokenID)
                    {
                        cout << "erase tag " << st->getValue(*it).name
                            << " for node " << nodeID << endl;
                        nodes[nodeID].secTag.erase(it);
                        rit = vCache[tokenID].erase(rit);
                        break;
                    }
                }
                if (rit == vCache[tokenID].end())
                            break;
            }
        }
    }
}

void DAGOptimizer::insertTag(int nodeID, int tag)
{
    cout << "Insert tag " << st->getValue(tag).name
        << " on node " << nodeID << endl;
    if (st->getValue(nodes[nodeID].priTag).addr == -1)
    {
        // switch priTag and secTag
        nodes[nodeID].secTag.push_back(nodes[nodeID].priTag);
        nodes[nodeID].priTag = tag;
    }
    else
    {
        nodes[nodeID].secTag.push_back(tag);
    }
    cout << "vCache tag " << st->getValue(tag).name
        << " for node " << nodeID << endl;
    vCache[tag].push_back(nodeID);
    cout << "now vCache[" << st->getValue(tag).name
        << "] = ";
    for (auto it = vCache[tag].begin(); it != vCache[tag].end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void DAGOptimizer::buildDAG()
{
    for (auto it = qt->begin(); it != qt->end(); ++it)
    {
        // Insert new node if needed
        int nodeID1 = insertNode(it->opr1);
        int nodeID2 = insertNode(it->opr2);
        switch (it->op)
        {
        case ADD:
        case MUL:
        case MINUS:
        case DIV:
            if (st->getValue(it->opr1).cat == C &&
                st->getValue(it->opr2).cat == C)
            {
                // C1 w C2
                TypeTableRecord ttr;
                int iaddr;
                int cid;
                if (isInteger(it->rst))
                {
                    int c = calcInteger(*it);
                    ttr.tval = INTEGER;
                    iaddr = ict->entry(c);
                    cid = st->entry(numToString<int>(c), tt->getID(ttr), C, iaddr);
                }
                else if (isFloat(it->opr1))
                {
                    float c = calcFloat(*it);
                    ttr.tval = FLOAT;
                    iaddr = fct->entry(c);
                    cid = st->entry(numToString<float>(c), tt->getID(ttr), C, iaddr);
                }
                int cnodeID = insertNode(cid);
                removeTag(it->rst);
                insertTag(cnodeID, it->rst);
            }
            else
            {
                // B w C
                removeTag(it->rst);
                int rstnodeID = -1;
                for (auto nit = nodes.rbegin(); nit != nodes.rend(); ++nit)
                {
                    bool f1 = false, f2 = false, f3 = false, f4 = false;
                    if (nit->op == it->op)
                    {
                        // Non-switchable
                        f1 = find(vCache[it->opr1].begin(), vCache[it->opr1].end(), nit->pl) != vCache[it->opr1].end();
                        f2 = find(vCache[it->opr2].begin(), vCache[it->opr2].end(), nit->pr) != vCache[it->opr2].end();
                        // Switchable
                        f3 = find(vCache[it->opr1].begin(), vCache[it->opr1].end(), nit->pr) != vCache[it->opr1].end();
                        f4 = find(vCache[it->opr2].begin(), vCache[it->opr2].end(), nit->pl) != vCache[it->opr2].end();
                        if (((it->op == MINUS || it->op == DIV) && (f1 && f2)) ||
                            ((it->op == ADD || it->op == MUL) && ((f1 && f2) || (f3 && f4))))
                        {
                            rstnodeID = nit->id;
                            break;
                        }
                    }
                }
                if (rstnodeID != -1)
                {
                    insertTag(rstnodeID, it->rst);
                }
                else
                {
                    cout << "Insert " << st->getValue(it->rst).name << endl;
                    DAGNode n;
                    n.id = nodes.size();
                    n.op = it->op;
                    n.priTag = it->rst;
                    n.pl = nodeID1;
                    n.pr = nodeID2;
                    nodes.push_back(n);
                    vCache[it->rst].push_back(n.id);
                }
            }
            break;
        case ASSIGN:
            removeTag(it->rst);
            insertTag(nodeID1, it->rst);
            break;
        case BLANK:
            break;
        }
    }
}

QuadrupleTable DAGOptimizer::optimize()
{
    QuadrupleTable new_qt;
    Quadruple q;
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if (it->op != BLANK)
        {
            q.op = it->op;
            q.opr1 = nodes[it->pl].priTag;
            q.opr2 = nodes[it->pr].priTag;
            q.rst = it->priTag;
            optimizeSymbolTable(q);
            new_qt.push_back(q);
        }
        if (st->getValue(it->priTag).addr != -1 &&
            st->getValue(it->priTag).cat == V &&
            !it->secTag.empty())
        {
            for (auto iit = it->secTag.begin(); iit != it->secTag.end(); ++iit)
            {
                if (st->getValue(*iit).addr != -1 &&
                    st->getValue(*iit).cat == V)
                {
                    q.op = ASSIGN;
                    q.opr1 = it->priTag;
                    q.opr2 = -1;
                    q.rst = *iit;
                    optimizeSymbolTable(q);
                    new_qt.push_back(q);
                }
            }
        }
    }
    return new_qt;
}

void DAGOptimizer::enableTemp(vector<SymbolTableRecord> &t, int id)
{
    t[id].isUsed = true;
    t[id].isTemp = t[id].addr == -1;
    if (t[id].isTemp)
    {
        VallRecord r;
        r.offset = vall->totoffset;
        vall->v.push_back(r);
        if (tt->getValue(t[id].type).tval == INTEGER)
            vall->totoffset += INTSIZE;
        else
            vall->totoffset += FLOATSIZE;
        st->entryAddr(id, r.offset);
    }
}

void DAGOptimizer::optimizeSymbolTable(const Quadruple &q)
{
    vector<SymbolTableRecord> &t = st->getTable();
    enableTemp(t, q.opr1);
    enableTemp(t, q.rst);
    if (q.op != BLANK)
        enableTemp(t, q.opr2);
}

int DAGOptimizer::calcInteger(const Quadruple &q)
{
    int x = getIntConst(q.opr1);
    int y = getIntConst(q.opr2);
    switch (q.op)
    {
    case ADD:
        return x + y;
    case MINUS:
        return x - y;
    case MUL:
        return x * y;
    case DIV:
        return x / y;
    default:
        return 0;
    }
}

float DAGOptimizer::calcFloat(const Quadruple &q)
{
    float x, y;
    if (isInteger(q.opr1))
        x = float(getIntConst(q.opr1));
    else x = getFloatConst(q.opr1);
    if (isInteger(q.opr2))
        y = float(getIntConst(q.opr2));
    else y = getFloatConst(q.opr2);
    switch (q.op)
    {
    case ADD:
        return x + y;
    case MINUS:
        return x - y;
    case MUL:
        return x * y;
    case DIV:
        return x / y;
    default:
        return 0;
    }
}
