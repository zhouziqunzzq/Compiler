#include<bits/stdc++.h>
#include "Scanner.h"
#include "Category.h"
#include <sstream>

using namespace std;

Scanner::Scanner(string s, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
        StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
        SymbolTable *st) : kt(kt), dt(dt), cct(cct),
        strct(strct), ict(ict), fct(fct), st(st), content(s)
{
    curIndex = 0;
    curState = 1;
    lastState = 1;
    isEnd = false;
    // Initialize Handle Functions
    hft[1] = &handleEmpty;
    hft[12] = &handleKeywordIdentifier;
    hft[13] = &handleFloatConst;
    hft[14] = &handleIntConst;
    hft[15] = &handleCharConst;
    hft[16] = &handleStringConst;
    hft[17] = &handleDelimiter;
    hft[19] = &handleDelimiter;
    hft[22] = hft[25] = &handleComment;
    hft[28] = &handleScientificNotationConstant;
}

const Token& Scanner::getLastToken() const
{
    return lastToken;
}

void Scanner::reset()
{
    buffer.clear();
    curState = 1;
}

void Scanner::rewind()
{
    --curIndex;
    buffer.erase(buffer.end() - 1);
}

void Scanner::next()
{
    if (isEnd)
    {
        lastToken.type = END;
        return;
    }
    while (curIndex != content.length() &&
            !(curState == 1 && lastState != 1))
    {
        //cout << "curState: " << curState << endl;
        //cout << "length: " << content.length() << endl;
        //cout << "curIndex: " << curIndex << endl;
        lastState = curState;
        char c = content[curIndex++];
        buffer += c;
        if (sct.hasNextState(curState, c))
            curState = sct.getNextState(curState, c);
        else
        {
            lastToken.type = ERROR;
            return;
        }
        if (hft.find(curState) != hft.end())
            (this->*hft[curState])();
    }
    lastState = 1;
    // Ignore all blank char
    while (curIndex != content.length() &&
            (content[curIndex] == '\n' || content[curIndex] == '\r'
             || content[curIndex] == '\t' || content[curIndex] == ' '))
    {
        ++curIndex;
    }
    if (curIndex == content.length())
        isEnd = true;
}

template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

void Scanner::handleEmpty()
{
    reset();
}

void Scanner::handleKeywordIdentifier()
{
    rewind();
    if (kt->has(buffer))
    {
        // Keyword
        lastToken.type = KEYWORD;
        lastToken.id = kt->getID(buffer);
        lastToken.word = buffer;
    }
    else
    {
        // Identifier
        lastToken.type = IDENTIFIER;
        lastToken.id = st->entry(buffer, -1, CC, -1);
        lastToken.word = buffer;
    }
    reset();
}

void Scanner::handleFloatConst()
{
    rewind();
    float f = stringToNum<float>(buffer);
    lastToken.type = FLOATCONST;
    lastToken.id = fct->entry(f);
    lastToken.word = buffer;
    reset();
}

void Scanner::handleScientificNotationConstant()
{
    rewind();
    size_t posE = buffer.find("e");
    float myBase = stringToNum<float>(buffer.substr(0, posE));
    int myExp = stringToNum<int>(buffer.substr(posE + 1));
    float f = myBase * pow(10, myExp);
    lastToken.type = FLOATCONST;
    lastToken.id = fct->entry(f);
    lastToken.word = buffer;
    reset();
}

void Scanner::handleIntConst()
{
    rewind();
    int i = stringToNum<int>(buffer);
    lastToken.type = INTCONST;
    lastToken.id = ict->entry(i);
    lastToken.word = buffer;
    reset();
}

void Scanner::handleCharConst()
{
    rewind();
    if (buffer.length() == 2)
    {
        // Empty char constant error
        lastToken.type = ERROR;
        lastToken.id = -1;
        lastToken.word = buffer;
    }
    else
    {
        char c = buffer[1];
        lastToken.type = CHARCONST;
        lastToken.id = cct->entry(c);
        lastToken.word = buffer;
    }
    reset();
}

void Scanner::handleStringConst()
{
    rewind();
    string s = buffer.length() > 2 ? buffer.substr(1, buffer.length() - 2) : "";
    lastToken.type = STRCONST;
    lastToken.id = strct->entry(s);
    lastToken.word = buffer;
    reset();
}

void Scanner::handleDelimiter()
{
    rewind();
    if (dt->has(buffer))
    {
        lastToken.type = DELIMITER;
        lastToken.id = dt->getID(buffer);
        lastToken.word = buffer;
    }
    else
    {
        lastToken.type = ERROR;
        lastToken.id = -1;
        lastToken.word = buffer;
    }
    reset();
}

void Scanner::handleComment()
{
    //rewind();
    lastToken.id = -1;
    lastToken.word = buffer;
    if (curState == 25 &&
            (buffer.length() < 4 || buffer[buffer.length()-2] != '*'))
    {
        lastToken.type = ERROR;
    }
    else
    {
        lastToken.type = COMMENT;
    }
    reset();
}
