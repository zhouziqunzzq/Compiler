#ifndef DAGOPTIMIZER_H
#define DAGOPTIMIZER_H

#include <vector>
#include "Quadruple.h"
#include "QuadrupleTable.h"
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
        DAGOptimizer(QuadrupleTable *qt);
        QuadrupleTable optimize();

    protected:

    private:
        vector<DAGNode> node;
        QuadrupleTable *qt;
        void buildDAG();


};

#endif // DAGOPTIMIZER_H
