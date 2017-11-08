#ifndef SCANNER_H
#define SCANNER_H


class Scanner
{
    public:
        Scanner();

    protected:

    private:
        string content;
        int curIndex;
        int curState;
        int lastState;
        Token lastToken;
        StateChangeTable sct;
        HandleFuncTable hft;
        string buffer;
        KeywordTable *kt;
        DelimiterTable *dt;
        CharConstTable *ct;
        StrConstTable *sct;
        IntConstTable *ict;
        FloatConstTable *fct;
        SymbolTable *st;
};

#endif // SCANNER_H
