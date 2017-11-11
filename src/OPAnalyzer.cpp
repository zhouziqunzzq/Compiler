#include<bits/stdc++.h>
#include "OPAnalyzer.h"

using namespace std;

OPAnalyzer::OPAnalyzer(Scanner *sc) : sc(sc)
{
	init_mp();
	init_g();
}

void OPAnalyzer::init_mp()
{
	mp["+"]["+"] = '>';
	mp["+"]["-"] = '>';
	mp["+"]["*"] = '<';
	mp["+"]["/"] = '<';
	mp["+"]["("] = '<';
	mp["+"][")"] = '>';
	mp["+"]["id"] = '<';
	mp["+"]["c"] = '<';

	mp["-"]["+"] = '>';
	mp["-"]["-"] = '>';
	mp["-"]["*"] = '<';
	mp["-"]["/"] = '<';
	mp["-"]["("] = '<';
	mp["-"][")"] = '>';
	mp["-"]["id"] = '<';
	mp["-"]["c"] = '<';

	mp["*"]["+"] = '>';
	mp["*"]["-"] = '>';
	mp["*"]["*"] = '>';
	mp["*"]["/"] = '>';
	mp["*"]["("] = '<';
	mp["*"][")"] = '>';
	mp["*"]["id"] = '<';
	mp["*"]["c"] = '<';

	mp["/"]["+"] = '>';
	mp["/"]["-"] = '>';
	mp["/"]["*"] = '>';
	mp["/"]["/"] = '>';
	mp["/"]["("] = '<';
	mp["/"][")"] = '>';
	mp["/"]["id"] = '<';
	mp["/"]["c"] = '<';

	mp["("]["+"] = '<';
	mp["("]["-"] = '<';
	mp["("]["*"] = '<';
	mp["("]["/"] = '<';
	mp["("]["("] = '<';
	mp["("][")"] = '=';
	mp["("]["id"] = '<';
	mp["("]["c"] = '<';

	mp[")"]["+"] = '>';
	mp[")"]["-"] = '>';
	mp[")"]["*"] = '>';
	mp[")"]["/"] = '>';
	mp[")"][")"] = '>';

	mp["id"]["+"] = '>';
	mp["id"]["-"] = '>';
	mp["id"]["*"] = '>';
	mp["id"]["/"] = '>';
	mp["id"][")"] = '>';

	mp["c"]["+"] = '>';
	mp["c"]["-"] = '>';
	mp["c"]["*"] = '>';
	mp["c"]["/"] = '>';
	mp["c"][")"] = '>';
}

void OPAnalyzer::init_g()
{
	g["E+T"] = "E";
	g["E-T"] = "E";
	g["T"] = "E";
	g["T*F"] = "T";
	g["T/F"] = "T";
	g["F"] = "T";
	g["GF"] = "F";
	g["(E)"] = "F";
	g["id"] = "GF";
	g["c"] = "GF";
}

string OPAnalyzer::getWord(Token tmp)
{
	string res;
	if(tmp.type == IDENTIFIER)
		res = "id";
	else if((tmp.type==CHARCONST) || (tmp.type==STRCONST) || (tmp.type==INTCONST) || (tmp.type==FLOATCONST))
		res = "c";
	else res = tmp.word;
	return res;
}

string OPAnalyzer::getS(stack<Token> &st)
{
	Token tmp = st.top();
	st.pop();
	string res = tmp.word;
	while(mp[getWord(st.top())][getWord(tmp)] != '<')
	{
		tmp = st.top();
		st.pop();
		res += tmp.word;
	}
	return res;
}

bool OPAnalyzer::E()
{
	stack<Token> st;
	bool flag = true;
	while(!st.empty()) st.pop();
	Token t1 = sc->getLastToken();
	while(t1.type != END)
	{
		if(st.empty())
		{
			st.push(t1);
			sc->next();
			t1 = sc->getLastToken();
		}
		Token t2 = st.top();
		st.pop();
		auto it1 = mp.find(getWord(t1));
		auto it2 = mp.find(getWord(t2));
		if((it1 != mp.end()) && (it2 != mp.end()))
		{
			if(mp[getWord(t2)][getWord(t1)] == '>')
			{
				string stmp = getS(st);
				auto ts = g.find(stmp);
				if(ts != g.end())
				{
					Token to(KEYWORD, g[stmp], -1);
					st.push(to);
				}
				else flag = false;
			}
			else
			{
				st.push(t1);
				sc->next();
				t1 = sc->getLastToken();
			}
		}
		else flag = false;
		if(flag == false) break;
	}
	return flag;
}
