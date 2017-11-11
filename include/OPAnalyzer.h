#ifndef OPAnalyzer_h
#define OPAnalyzer_h

#include<bits/stdc++.h>
#include "Token.h"
#include "Scanner.h"

using namespace std;

class OPAnalyzer
{
	private:
		Scanner *sc;
		void init_mp();
		map<string, map<string, char>> mp;
		string getWord(Token tmp);
		string getS(stack<Token> &st);
		void init_g();
		map<string, string> g;
	
	public:
		bool E();
		OPAnalyzer(Scanner *sc);
};

#endif
