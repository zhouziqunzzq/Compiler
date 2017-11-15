#include "Token.h"

using namespace std;

Token::Token():
    type(KEYWORD), word(""), id(-1) {}

Token::Token(TokenType t, string w, int id):
    type(t), word(w), id(id) {}

bool Token::operator==(const Token& t)
{
    return this->word == t.word &&
           this->type == t.type &&
           this->id   == t.id;
}
