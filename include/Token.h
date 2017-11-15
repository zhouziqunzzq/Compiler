#ifndef TOKEN_H
#define TOKEN_H

#include<string>
using namespace std;

enum TokenType
{
	KEYWORD = 1,
	DELIMITER = 2,
	CHARCONST = 3,
	STRCONST = 4,
	INTCONST = 5,
	FLOATCONST = 6,
	IDENTIFIER = 7,
	COMMENT = 8,
	ERROR = -1,
	END = -2
};

class Token
{
	public:
		TokenType type;
		string word;
		int id;

		Token();
		Token(TokenType t, string w, int id);
		bool operator==(const Token& t1);
};

#endif
