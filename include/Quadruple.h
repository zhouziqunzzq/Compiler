#ifndef QUADRUPLE_H_INCLUDED
#define QUADRUPLE_H_INCLUDED

using namespace std;
enum Operation
{
    ADD = 0,
    MINUS = 1,
    MUL = 2,
    DIV = 3,
    ASSIGN = 4
};

struct Quadruple
{
    Operation op;
    int opr1;
    int opr2;
    int rst;

    Quadruple(Operation op, int opr1, int opr2, int rst) :
        op(op), opr1(opr1), opr2(opr2), rst(rst) {}
};

#endif // QUADRUPLE_H_INCLUDED
