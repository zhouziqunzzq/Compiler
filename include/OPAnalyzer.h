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
		struct cmp
		{
			bool operator()(const string s1, const string s2) const
			{
				bool flag = false;
				string tmps1, tmps2;
				bool add = 1;
				for(string::size_type i=0; i<s1.size(); i++)
				{
					if((s1[i]=='+') || (s1[i]=='-') || (s1[i]=='*') || (s1[i]=='/') || (s1[i]=='(') || (s1[i]==')') || (s1[i]=='c'))
						tmps1 += s1[i], add = 1;
					else if((i!=s1.size()-1) && (s1[i]=='i') && (s1[i+1]=='d'))
						tmps1 += s1[i], add = 1;
					else if((i!=0) && (s1[i-1]=='i') && (s1[i]=='d'))
						tmps1 += s1[i], add = 1;
					else if(add == 1) tmps1 += 'x', add = 0;
				}
				add = 1;
				for(string::size_type i=0; i<s2.size(); i++)
				{
					if((s2[i]=='+') || (s2[i]=='-') || (s2[i]=='*') || (s2[i]=='/') || (s2[i]=='(') || (s2[i]==')') || (s2[i]=='c'))
						tmps2 += s2[i], add = 1;
					else if((i!=s2.size()-1) && (s2[i]=='i') && (s2[i+1]=='d'))
						tmps2 += s2[i], add = 1;
					else if((i!=0) && (s2[i-1]=='i') && (s2[i]=='d'))
						tmps2 += s2[i], add = 1;
					else if(add == 1) tmps2 += 'x', add = 0;
				}
				if(tmps1.compare(tmps2) == 0) flag = true;
				return flag;
			}
		};
		void init_g();
		map<string, string, cmp> g;
		void init_vcat();
		map<string, bool> v_cat;
        bool isEnd(string s);

	public:
		bool E();
		OPAnalyzer(Scanner *sc);
};

#endif
