#ifndef RDAnalyzer_H
#define RDAnalyzer_H

#include "Scanner.h"

class RDAnalyzer
{
private:
    Scanner *sc;

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
