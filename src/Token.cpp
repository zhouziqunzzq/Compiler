#include "Token.h"

using namespace std;

Token::Token(TokenType t, string &w, int id):
	type(t), word(w), id(id){}
