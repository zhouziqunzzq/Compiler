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
        }
        printf("(%s, %d, %d, %d)\n", ops.c_str(), it->opr1, it->opr2, it->rst);
    }
}

int main(int argc, char *argv[])
{
    string test = "int a = 1.2 + 2 * 3; a = 123.234;\n";//((1+2)*3)/1e4; a = 3 + x / 3.14;\n";
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
    st.print();
    ict.print("IntConstTable");
    fct.print("FloatConstTable");
    printQT(qt);

    return 0;
}
