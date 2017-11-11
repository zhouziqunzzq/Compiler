#ifndef RDAnalyzer_H
#define RDAnalyzer_H

#include "Scanner.h"
#include "OPAnalyzer.h"

class RDAnalyzer
{
private:
    Scanner *sc;
    OPAnalyzer opa;
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

public:
    RDAnalyzer(Scanner *sc);
    bool analyze();
};

#endif
