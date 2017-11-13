#include<bits/stdc++.h>
#include "DAGOptimizer.h"
#include "Quadruple.h"
#include "QuadrupleTable.h"
using namespace std;

DAGOptimizer::DAGOptimizer(QuadrupleTable *qt) : qt(qt)
{
    buildDAG();
}

void DAGOptimizer::buildDAG()
{
    for (auto it = qt->begin(); it != qt->end(); ++it)
    {
        // Insert new node if needed

        switch (it->op)
        {
        case ADD:
        case MUL:
            break;
        case MINUS:
        case DIV:
            break;
        case ASSIGN:
            break;
        }
    }
}

QuadrupleTable DAGOptimizer::optimize()
{
    QuadrupleTable new_qt;
    return new_qt;
}
