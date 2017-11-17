#ifndef RDAnalyzer_H
#define RDAnalyzer_H

#include "Scanner.h"
#include "OPAnalyzer.h"
#include "QuadrupleTable.h"
#include "utils.h"
#include <stack>

class RDAnalyzer
{
private:
    Scanner *sc;
    QuadrupleTable *qt;
    OPAnalyzer opa;
    stack<Token> sem;
    int entloop = 0;
    bool constflag = 0;
    bool constintflag = 0;
    bool constfloatflag = 0;
    bool intflag = 0;
    bool floatflag = 0;
    Token lastIdentifier;
    bool PG();
    bool ST();
    bool VS();
    bool AS();
    bool VD();
    bool TP();
    bool IT();
    bool IFD();
    bool PD();
    bool IS();
    bool GF();
    void Ent();
    void Typ(Token tmp);
    bool ASSI();
    void INITFLAG();

public:
    RDAnalyzer(Scanner *sc, QuadrupleTable *qt);
    bool analyze();
};

#endif
