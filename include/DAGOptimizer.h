#ifndef DAGOPTIMIZER_H
#define DAGOPTIMIZER_H

#include <vector>
#include "Quadruple.h"
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
        DAGOptimizer();

    protected:

    private:
        vector<DAGNode> node;
};

#endif // DAGOPTIMIZER_H
