#include<bits/stdc++.h>
#include "DAGOptimizer.h"
#include "Quadruple.h"
#include "QuadrupleTable.h"
#include "Category.h"
using namespace std;

DAGOptimizer::DAGOptimizer(QuadrupleTable *qt, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
            StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
            SymbolTable *st) : kt(kt), dt(dt), cct(cct),
        strct(strct), ict(ict), fct(fct), st(st), qt(qt)
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
        int nodeID = vCache[tokenID];
        if (tokenID != nodes[nodeID].priTag)
        {
            auto it = nodes[nodeID].secTag.begin();
            for (; it != nodes[nodeID].secTag.end(); ++it)
            {
                if (*it == tokenID)
                {
                    nodes[nodeID].secTag.erase(it);
                    return;
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
