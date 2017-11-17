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

class ASMGenerator
{
public:
    ASMGenerator(QuadrupleTable *qt, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
                 StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
                 SymbolTable *st, TypeTable *tt, Vall *vall);

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

    void fillActiveInfo();
};

#endif // ASMGENERATOR_H
