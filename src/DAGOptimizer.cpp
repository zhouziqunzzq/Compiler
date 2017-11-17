#include<bits/stdc++.h>
#include "DAGOptimizer.h"
#include "Quadruple.h"
#include "QuadrupleTable.h"
#include "Category.h"
#define isInteger(x) tt->getValue(st->getValue((x)).type).tval == INTEGER
#define isFloat(x) tt->getValue(st->getValue((x)).type).tval == FLOAT
#define getIntConst(x) ict->getValue(st->getValue((x)).addr)
#define getFloatConst(x) fct->getValue(st->getValue((x)).addr)
using namespace std;

DAGOptimizer::DAGOptimizer(QuadrupleTable *qt, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
            StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
            SymbolTable *st, TypeTable *tt) : kt(kt), dt(dt), cct(cct),
        strct(strct), ict(ict), fct(fct), st(st), tt(tt), qt(qt)
{
    buildDAG();
}

int DAGOptimizer::insertNode(int tokenID)
{
    if (tokenID < 0)
        return tokenID;
    else if (vCache.find(tokenID) != vCache.end())
        return vCache[tokenID];
    else
    {
        DAGNode n;
        n.id = nodes.size();
        n.priTag = tokenID;
        vCache[tokenID] = n.id;
        nodes.push_back(n);
        return n.id;
    }
}

void DAGOptimizer::removeTag(int tokenID)
{
    if (vCache.find(tokenID) != vCache.end())
    {
        int nodeID;
        for (auto rit = vCache[tokenID].rbegin();
            rit != vCache[tokenID].rend(); ++rit)
        {
            nodeID = *rit;
            if (tokenID != nodes[nodeID].priTag)
            {
                for (auto it = nodes[nodeID].secTag.begin();
                    it != nodes[nodeID].secTag.end(); ++it)
                {
                    if (*it == tokenID)
                    {
                        nodes[nodeID].secTag.erase(it);
                        break;
                    }
                }
            }
        }
    }
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
            // C1 w C2
            if (st->getValue(it->opr1).cat == C &&
                st->getValue(it->opr2).cat == C)
            {
                if (isInteger(it->opr1))
                {
                    int c = calcInteger(*it);

                }
                else if (isFloat(it->opr1))
                {
                    float c = calcFloat(*it);
                }
                break;
            }
            break;
        case ASSIGN:
            removeTag(it->rst);
            nodes[nodeID1].secTag.push_back(it->rst);
            vCache[it->rst] = nodeID1;
            break;
        }
    }
}

QuadrupleTable DAGOptimizer::optimize()
{
    QuadrupleTable new_qt;
    return new_qt;
}

int DAGOptimizer::calcInteger(const Quadruple &q) const
{
    switch (q.op)
    {
    case ADD:
        return getIntConst(q.opr1) + getIntConst(q.opr2);
    case MINUS:
        return getIntConst(q.opr1) - getIntConst(q.opr2);
    case MUL:
        return getIntConst(q.opr1) * getIntConst(q.opr2);
    case DIV:
        return getIntConst(q.opr1) / getIntConst(q.opr2);
    }
}

float DAGOptimizer::calcFloat(const Quadruple &q) const
{
    switch (q.op)
    {
    case ADD:
        return getFloatConst(q.opr1) + getFloatConst(q.opr2);
    case MINUS:
        return getFloatConst(q.opr1) - getFloatConst(q.opr2);
    case MUL:
        return getFloatConst(q.opr1) * getFloatConst(q.opr2);
    case DIV:
        return getFloatConst(q.opr1) / getFloatConst(q.opr2);
    }
}
