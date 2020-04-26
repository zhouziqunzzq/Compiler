#ifndef ASMGENERATOR_H
#define ASMGENERATOR_H

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

class ASMGenerator {
public:
    ASMGenerator(QuadrupleTable *qt, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
                 StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
                 SymbolTable *st, TypeTable *tt, Vall *vall);

    string gen();

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
    QuadrupleTable *qt;

    vector<string> obj;
    int rdl;
    bool rdlActive;
    string opcode[10];

    void fillActiveInfo();

    void genHeader();

    void genBody();

    void genMOV(int id);

    void genST(int id);

    void genOP(int op, int id);

    void genFooter();
};

#endif // ASMGENERATOR_H
