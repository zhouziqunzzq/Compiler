#include <bits/stdc++.h>
#include "Scanner.h"
#include "Token.h"
#include "KeywordTable.h"
#include "DelimiterTable.h"
#include "ConstTable.h"
#include "SymbolTable.h"
using namespace std;

int main(int argc, char *argv[])
{
    /*Scanner(string s, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
        StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
        SymbolTable *st)*/
    string test = "a+b=1.2e5;\n";
    KeywordTable kt;
    DelimiterTable dt;
    CharConstTable cct;
    StrConstTable strct;
    IntConstTable ict;
    FloatConstTable fct;
    SymbolTable st;
    Scanner sc(test, &kt, &dt, &cct, &strct, &ict, &fct, &st);
    while (sc.getLastToken().type != ERROR &&
            sc.getLastToken().type != END)
    {
        sc.next();
        //system("pause");
        if (sc.getLastToken().type != END)
            cout << sc.getLastToken().word << endl;
        else
            cout << "END" << endl;
    }
    return 0;
}
