#ifndef DAGOPTIMIZER_H
#define DAGOPTIMIZER_H

#include <vector>
#include "Quadruple.h"
#include "QuadrupleTable.h"
#include "SymbolTable.h"
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
            SymbolTable *st, SymbolTable *tst);
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
        SymbolTable *tst;
        vector<DAGNode> node;
        map<int, bool> vCache;  // cache for judging whether a given variable token id exists
        map<int, bool> tCaChe;  // cache for judging whether a given temp variable token id exists
        QuadrupleTable *qt;
        void buildDAG();


};

#endif // DAGOPTIMIZER_H
