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
#include "utils.h"

using namespace std;

struct DAGNode {
    int id;
    int priTag;
    vector<int> secTag;
    Operation op;
    int pl, pr;

    DAGNode() {
        id = -1;
        priTag = -1;
        op = BLANK;
        pl = -1;
        pr = -1;
    }
};

class DAGOptimizer {
public:
    DAGOptimizer(QuadrupleTable *qt, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
                 StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
                 SymbolTable *st, TypeTable *tt, Vall *vall);

    QuadrupleTable optimize();

    void print();

protected:

private:
    KeywordTable *kt;
    DelimiterTable *dt;
    CharConstTable *cct;
    StrConstTable *strct;
    IntConstTable *ict;
    FloatConstTable *fct;
    SymbolTable *st;
    TypeTable *tt;
    Vall *vall;
    vector<DAGNode> nodes;
    map<int, vector<int> > vCache;  // cache for judging whether a given variable token id exists
    // TokenID -> vector<node.id>
    QuadrupleTable *qt;

    void buildDAG();

    int insertNode(int tokenID);

    void removeTag(int tokenID);

    void insertTag(int nodeID, int tag);

    int calcInteger(const Quadruple &q);

    float calcFloat(const Quadruple &q);

    void optimizeSymbolTable(const Quadruple &q);

    void enableTemp(vector<SymbolTableRecord> &t, int id);

};

#endif // DAGOPTIMIZER_H
