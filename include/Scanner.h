#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"
#include "ConstTable.h"
#include "SymbolTable.h"
#include "KeywordTable.h"
#include "DelimiterTable.h"
#include "StateChangeTable.h"
#include "Vall.h"
#include "TypeTable.h"
#include "utils.h"
#include <string>
using namespace std;

class Scanner
{
    typedef void(Scanner::*HandleFuncPtr)();
    typedef map<int, HandleFuncPtr> HandleFuncTable;
public:
    Scanner(string s, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
            StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
            SymbolTable *st, Vall *vall, TypeTable *tt);
    KeywordTable *kt;
    DelimiterTable *dt;
    CharConstTable *cct;
    StrConstTable *strct;
    IntConstTable *ict;
    FloatConstTable *fct;
    SymbolTable *st;
    Vall *vall;
    TypeTable *tt;
    void next();
    const Token& getLastToken() const;
    const size_t& getCurIndex() const;

protected:

private:
    string content;
    string buffer;
    size_t curIndex;
    int curState;
    int lastState;
    bool isEnd;
    Token lastToken;
    StateChangeTable sct;
    HandleFuncTable hft;
    void reset();
    void rewind();

    void handleEmpty();
    void handleKeywordIdentifier();
    void handleFloatConst();
    void handleIntConst();
    void handleCharConst();
    void handleStringConst();
    void handleDelimiter();
    void handleComment();
    void handleScientificNotationConstant();
};

#endif // SCANNER_H
