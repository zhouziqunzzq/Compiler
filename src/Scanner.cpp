#include<bits/stdc++.h>
#include "Scanner.h"
#include <sstream>
#include <utility>

using namespace std;

Scanner::Scanner(string s, KeywordTable *kt, DelimiterTable *dt, CharConstTable *cct,
                 StrConstTable *strct, IntConstTable *ict, FloatConstTable *fct,
                 SymbolTable *st, Vall *vall, TypeTable *tt) :
        kt(kt), dt(dt), cct(cct),
        strct(strct), ict(ict), fct(fct), st(st), vall(vall),
        tt(tt), content(std::move(s)) {
    curIndex = 0;
    curState = 1;
    lastState = 1;
    isEnd = false;
    // Initialize Handle Functions
    hft[1] = &Scanner::handleEmpty;
    hft[12] = &Scanner::handleKeywordIdentifier;
    hft[13] = &Scanner::handleFloatConst;
    hft[14] = &Scanner::handleIntConst;
    hft[15] = &Scanner::handleCharConst;
    hft[16] = &Scanner::handleStringConst;
    hft[17] = &Scanner::handleDelimiter;
    hft[19] = &Scanner::handleDelimiter;
    hft[22] = hft[25] = &Scanner::handleComment;
    hft[28] = &Scanner::handleScientificNotationConstant;
}

const Token &Scanner::getLastToken() const {
    return lastToken;
}

const size_t &Scanner::getCurIndex() const {
    return curIndex;
}

void Scanner::reset() {
    buffer.clear();
    curState = 1;
}

void Scanner::rewind() {
    --curIndex;
    buffer.erase(buffer.end() - 1);
}

void Scanner::next() {
    if (isEnd) {
        lastToken.type = END;
        return;
    }
    while (curIndex != content.length() &&
           !(curState == 1 && lastState != 1)) {
        lastState = curState;
        char c = content[curIndex++];
        buffer += c;
        if (sct.hasNextState(curState, c))
            curState = sct.getNextState(curState, c);
        else {
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
            || content[curIndex] == '\t' || content[curIndex] == ' ')) {
        ++curIndex;
    }
    if (curIndex == content.length())
        isEnd = true;
}

void Scanner::handleEmpty() {
    reset();
}

void Scanner::handleKeywordIdentifier() {
    rewind();
    if (kt->has(buffer)) {
        // Keyword
        lastToken.type = KEYWORD;
        lastToken.id = kt->getID(buffer);
        lastToken.word = buffer;
    } else {
        // Identifier
        lastToken.type = IDENTIFIER;
        lastToken.id = st->entry(buffer, -1, C, -1);
        lastToken.word = buffer;
    }
    reset();
}

void Scanner::handleFloatConst() {
    rewind();
    auto f = stringToNum<float>(buffer);
    lastToken.type = FLOATCONST;
    lastToken.id = st->entry(buffer, tt->entry(FLOAT, -1),
                             C, fct->entry(f));
    //lastToken.id = fct->entry(f);
    lastToken.word = buffer;
    reset();
}

void Scanner::handleScientificNotationConstant() {
    rewind();
    size_t posE = buffer.find('e');
    auto myBase = stringToNum<float>(buffer.substr(0, posE));
    int myExp = stringToNum<int>(buffer.substr(posE + 1));
    float f = myBase * static_cast<float>(pow(10, myExp));
    lastToken.type = FLOATCONST;
    lastToken.id = st->entry(buffer, tt->entry(FLOAT, -1),
                             C, fct->entry(f));
    //lastToken.id = fct->entry(f);
    lastToken.word = buffer;
    reset();
}

void Scanner::handleIntConst() {
    rewind();
    int i = stringToNum<int>(buffer);
    lastToken.type = INTCONST;
    lastToken.id = st->entry(buffer, tt->entry(INTEGER, -1),
                             C, ict->entry(i));
    //lastToken.id = ict->entry(i);
    lastToken.word = buffer;
    reset();
}

void Scanner::handleCharConst() {
    rewind();
    if (buffer.length() == 2) {
        // Empty char constant error
        lastToken.type = ERROR;
        lastToken.id = -1;
        lastToken.word = buffer;
    } else {
        char c = buffer[1];
        lastToken.type = CHARCONST;
        lastToken.id = st->entry(buffer, tt->entry(CHAR, -1),
                                 C, cct->entry(c));
        //lastToken.id = cct->entry(c);
        lastToken.word = buffer;
    }
    reset();
}

void Scanner::handleStringConst() {
    rewind();
    string s = buffer.length() > 2 ? buffer.substr(1, buffer.length() - 2) : "";
    lastToken.type = STRCONST;
    lastToken.id = st->entry(buffer, tt->entry(STRING, -1),
                             C, strct->entry(s));
    //lastToken.id = strct->entry(s);
    lastToken.word = buffer;
    reset();
}

void Scanner::handleDelimiter() {
    rewind();
    if (dt->has(buffer)) {
        lastToken.type = DELIMITER;
        lastToken.id = dt->getID(buffer);
        lastToken.word = buffer;
    } else {
        lastToken.type = ERROR;
        lastToken.id = -1;
        lastToken.word = buffer;
    }
    reset();
}

void Scanner::handleComment() {
    //rewind();
    lastToken.id = -1;
    lastToken.word = buffer;
    if (curState == 25 &&
        (buffer.length() < 4 || buffer[buffer.length() - 2] != '*')) {
        lastToken.type = ERROR;
    } else {
        lastToken.type = COMMENT;
    }
    reset();
}
