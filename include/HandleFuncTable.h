#ifndef HANDLEFUNCTABLE_H
#define HANDLEFUNCTABLE_H

#include "Scanner.h"
#include <map>

using namespace std;

class HandleFuncTable;

typedef void(HandleFuncTable::*HandleFuncPtr)(Scanner*);

class HandleFuncTable
{
public:
    HandleFuncTable();
    map<int, HandleFuncPtr> table;
    static void handleEmpty(Scanner *s);
    static void handleKeywordIdentifier(Scanner *s);
    static void handleFloatConst(Scanner *s);
    static void handleIntConst(Scanner *s);
    static void handleCharConst(Scanner *s);
    static void handleStringConst(Scanner *s);
    static void handleSingleDelimiter(Scanner *s);
    static void handleDoubleDelimiter(Scanner *s);
    static void handleComment(Scanner *s);
    static void handleScientificNotationConstant(Scanner *s);
};

#endif // HANDLEFUNCTABLE_H
