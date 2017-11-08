#include <bits/stdc++.h>
#include "HandleFuncTable.h"
#include "Token.h"
#include "SymbolTable.h"
#include "Category.h"

using namespace std;

HandleFuncTable::HandleFuncTable()
{
    //ctor
}

void HandleFuncTable::handleEmpty(Scanner *s)
{
    s->reset();
}

void HandleFuncTable::handleKeywordIdentifier(Scanner *s)
{
    s->rewind();
    if (s->kt->has(s->buffer))
    {
        // Keyword
        s->lastToken.type = KEYWORD;
        s->lastToken.id = s->kt->getID(s->buffer);
        s->lastToken.word = s->buffer;
    }
    else
    {
        // Identifier
        s->lastToken.type = IDENTIFIER;
        s->lastToken.id = s->st->entry(s->buffer, -1, CC, -1);
        s->lastToken.word = s->buffer;
    }
    s->reset();
}

void HandleFuncTable::handleFloatConst(Scanner *s)
{
    //
}
void HandleFuncTable::handleIntConst(Scanner *s)
{
    //
}

void HandleFuncTable::handleCharConst(Scanner *s)
{
    //
}

void HandleFuncTable::handleStringConst(Scanner *s)
{
    //
}

void HandleFuncTable::handleSingleDelimiter(Scanner *s)
{
    //
}

void HandleFuncTable::handleDoubleDelimiter(Scanner *s)
{
    //
}

void HandleFuncTable::handleComment(Scanner *s)
{
    //
}

void HandleFuncTable::handleScientificNotationConstant(Scanner *s)
{
    //
}
