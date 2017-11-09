#include "Token.h"

using namespace std;

Token::Token():
    type(KEYWORD), word(""), id(-1) {}

Token::Token(TokenType t, string &w, int id):
    type(t), word(w), id(id) {}
