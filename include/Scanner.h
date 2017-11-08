#ifndef SCANNER_H
#define SCANNER_H

class Scanner;

#include "Token.h"
#include "ConstTable.h"
#include "SymbolTable.h"
#include "KeywordTable.h"
#include "DelimiterTable.h"
#include "HandleFuncTable.h"
#include <string>
using namespace std;

class Scanner
{
    public:
        Scanner(string s);

    protected:

    private:
        string content;
        string buffer;
        int curIndex;
        int curState;
        int lastState;
        Token lastToken;
        //StateChangeTable sct;
        HandleFuncTable hft;
        KeywordTable *kt;
        DelimiterTable *dt;
        CharConstTable *ct;
        StrConstTable *sct;
        IntConstTable *ict;
        FloatConstTable *fct;
        SymbolTable *st;
        void reset();
        void rewind();
        void next();

    friend class HandleFuncTable;
};

#endif // SCANNER_H
