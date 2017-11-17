#include <bits/stdc++.h>
#include "Scanner.h"
#include "Token.h"
#include "KeywordTable.h"
#include "DelimiterTable.h"
#include "ConstTable.h"
#include "SymbolTable.h"
#include "RDAnalyzer.h"
#include "Vall.h"
#include "QuadrupleTable.h"
#include "utils.h"
#include "DAGOptimizer.h"
using namespace std;

void testScanner(Scanner &sc)
{
    while (sc.getLastToken().type != ERROR &&
            sc.getLastToken().type != END)
    {
        sc.next();
        if (sc.getLastToken().type != END)
            cout << sc.getLastToken().word << endl;
        else
            cout << "END" << endl;
    }
}

void testAnalyzer(Scanner &sc, RDAnalyzer &ra)
{
    bool flag = ra.analyze();
    if (!flag)
    {
        printf("ERROR: \tInvalid token \"%s\" found at position %d.\n",
               sc.getLastToken().word.c_str(), sc.getCurIndex());
        if (ra.errorMsg != "")
            printf("\t%s\n", ra.errorMsg.c_str());
    }
    else
        printf("OK.\n");
}

void printQT(const QuadrupleTable &qt)
{
    string ops;
    for (auto it = qt.begin(); it != qt.end(); ++it)
    {
        switch(it->op)
        {
        case ADD:
            ops = "ADD";
            break;
        case MINUS:
            ops = "MINUS";
            break;
        case MUL:
            ops = "MUL";
            break;
        case DIV:
            ops = "DIV";
            break;
        case ASSIGN:
            ops = "ASSIGN";
            break;
        case BLANK:
            ops = "BLANK";
            break;
        }
        printf("(%s, %d, %d, %d)\n", ops.c_str(), it->opr1, it->opr2, it->rst);
    }
}

int main(int argc, char *argv[])
{
    string test = "int a, b = 1 + 2 + 3; int c = a * b + b; int d = b * a + 3.2;\n";
    KeywordTable kt;
    DelimiterTable dt;
    CharConstTable cct;
    StrConstTable strct;
    IntConstTable ict;
    FloatConstTable fct;
    SymbolTable st;
    Vall vall;
    TypeTable tt;
    Scanner sc(test, &kt, &dt, &cct, &strct, &ict, &fct, &st, &vall, &tt);

    //testScanner(sc);
    //st.print();

    QuadrupleTable qt;
    RDAnalyzer ra(&sc, &qt);

    testAnalyzer(sc, ra);

    printQT(qt);

    DAGOptimizer optimizer(&qt, &kt, &dt, &cct, &strct, &ict, &fct, &st, &tt, &vall);
    optimizer.print();
    st.print(false);
    ict.print("IntConstTable");
    fct.print("FloatConstTable");

    QuadrupleTable new_qt = optimizer.optimize();
    printQT(new_qt);
    st.print(true);

    return 0;
}
