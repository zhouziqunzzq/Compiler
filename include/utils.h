#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include<bits/stdc++.h>
#include "SymbolTable.h"
#include "ConstTable.h"
#include "Quadruple.h"

#define getTval(t) sc->tt->getValue(sc->st->getValue((t)).type).tval
#define getCat(t) sc->st->getValue((t)).cat
#define getIntVal(t) sc->ict->getValue(sc->st->getValue((t)).addr)
#define getFloatVal(t) sc->fct->getValue(sc->st->getValue((t)).addr)

using namespace std;

template<class Type>
Type stringToNum(const string &str) {
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

template<class Type>
string numToString(const Type &v) {
    stringstream ss;
    string s;
    ss << v;
    ss >> s;
    return s;
}

int calcConstResult(Operation op, int a, int b);

float calcConstResult(Operation op, float a, int b);

float calcConstResult(Operation op, int a, float b);

float calcConstResult(Operation op, float a, float b);

#endif // UTILS_H_INCLUDED
