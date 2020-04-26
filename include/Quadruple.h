#ifndef QUADRUPLE_H_INCLUDED
#define QUADRUPLE_H_INCLUDED

#include<bits/stdc++.h>

using namespace std;

enum Operation {
    BLANK = -1,
    ADD = 0,
    MINUS = 1,
    MUL = 2,
    DIV = 3,
    ASSIGN = 4
};

struct Quadruple {
    Operation op;
    int opr1;
    bool isActive1;
    int opr2;
    bool isActive2;
    int rst;
    bool isActiveR;

    Quadruple(Operation op, int opr1, int opr2, int rst) :
            op(op), opr1(opr1), isActive1(false),
            opr2(opr2), isActive2(false),
            rst(rst), isActiveR(false) {}

    Quadruple() {}
};

#endif // QUADRUPLE_H_INCLUDED
