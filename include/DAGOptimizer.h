#ifndef DAGOPTIMIZER_H
#define DAGOPTIMIZER_H

#include <vector>
#include "Quadruple.h"
#include "QuadrupleTable.h"
#include "ConstTable.h"
#include "SymbolTable.h"
#include "KeywordTable.h"
#include "DelimiterTable.h"
#include "StateChangeTable.h"
#include "Vall.h"
#include "TypeTable.h"
using namespace std;

struct DAGNode
{
    int id;
    int priTag;
    vector<int> secTag;
    Operation op;
    DAGNode* to;
};

class DAGOptimizer
{
    public:
        DAGOptimizer(QuadrupleTable *qt, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
            StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
            SymbolTable *st);
        QuadrupleTable optimize();

    protected:

    private:
        KeywordTable *kt;
        DelimiterTable *dt;
        CharConstTable *cct;
        StrConstTable *strct;
        IntConstTable *ict;
        FloatConstTable *fct;
        SymbolTable *st;
        vector<DAGNode> nodes;
        map<int, int> vCache;  // cache for judging whether a given variable token id exists
                                // TokenID -> node.id
        QuadrupleTable *qt;
        void buildDAG();
        int insertNode(int tokenID);
        void removeTag(int tokenID);

};

#endif // DAGOPTIMIZER_H
