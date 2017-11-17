#include<bits/stdc++.h>
#include "ASMGenerator.h"
using namespace std;

ASMGenerator::ASMGenerator(QuadrupleTable *qt, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
            StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
            SymbolTable *st, TypeTable *tt, Vall *vall) : kt(kt), dt(dt), cct(cct),
        strct(strct), ict(ict), fct(fct), st(st), tt(tt), vall(vall), qt(qt)
{
    fillActiveInfo();
}

void ASMGenerator::fillActiveInfo()
{
    vector<SymbolTableRecord> &t = st->getTable();
    for (auto it = t.begin(); it != t.end(); ++it)
    {
        if (it->isUsed || (!it->isUsed && it->cat
                          == V && it->addr != -1))
        {
            it->isActive = !it->isTemp;
        }
    }
    for (auto it = qt->rbegin(); it != qt->rend(); ++it)
    {
        it->isActiveR = t[it->rst].isActive;
        t[it->rst].isActive = false;
        it->isActive1 = t[it->opr1].isActive;
        t[it->opr1].isActive = true;
        if (it->opr2 != -1)
        {
            it->isActive2 = t[it->opr2].isActive;
            t[it->opr2].isActive = true;
        }
    }
}
