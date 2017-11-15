#include<bits/stdc++.h>
#include "OPAnalyzer.h"

using namespace std;

OPAnalyzer::OPAnalyzer(Scanner *sc) : sc(sc)
{
	init_mp();
	init_g();
	init_vcat();
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

void OPAnalyzer::init_vcat()
{
	v_cat["+"] = true;
	v_cat["-"] = true;
	v_cat["*"] = true;
	v_cat["/"] = true;
	v_cat["("] = true;
	v_cat[")"] = true;
	v_cat["id"] = true;
	v_cat["c"] = true;
}

bool OPAnalyzer::isEnd(string s)
{
    if (s == "+" || s == "-" || s == "*" || s == "/" ||
        s == "(" || s == ")" || s == "id" || s == "c" ||
        s == "E" || s == "T" || s == "F" || s == "GF")
        return false;
    else
        return true;
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
	string res = getWord(tmp);
	//cout << "st.empty: " << st.empty() << endl;
	while(!st.empty() && mp[getWord(st.top())][getWord(tmp)] != '<')
	{
		tmp = st.top();
		st.pop();
		res += getWord(tmp);
		if(st.empty()) break;
	}
	//cout << "res: " << res << endl;
	return res;
}

bool OPAnalyzer::E()
{
	stack<Token> st;
	bool flag = true, f2 = false;
	Token t1 = sc->getLastToken();
	while(true)
	{
		if(st.empty())
		{
			st.push(t1);
			sc->next();
			t1 = sc->getLastToken();
		}
		Token t2 = st.top();
		st.pop();
		// Something
		if(isEnd(getWord(t1)))
		{
			f2 = true;
			t1 = t2;
			t2 = st.top();
			st.pop();
		}
		if(v_cat.find(getWord(t2))!=v_cat.end())
		{
			st.push(t1);
			if(f2)
			{
				t1 = t2;
				t2 = st.top();
				st.pop();
			}
			else
			{
				sc->next();
				t1 = sc->getLastToken();
			}
			continue;
		}
		auto it1 = mp.find(getWord(t1));
		auto it2 = mp.find(getWord(t2));
		printf("t1: %s, t2: %s\n", t1.word.c_str(), t2.word.c_str());
		if((it1 != mp.end()) && (it2 != mp.end()))
		{
			if(mp[getWord(t2)][getWord(t1)] == '>')
			{
				string stmp = getS(st);
				printf("stmp: %s\n", stmp.c_str());
				auto ts = g.find(stmp);
				if(ts != g.end())
				{
					Token to(KEYWORD, g[stmp], -1);
					printf("g[stmp]: %s\n", g[stmp].c_str());
					//if (to.word != "")
                    st.push(to);
				}
				else flag = false;
			}
			else
			{
				st.push(t1);
				if(f2)
				{
					t1 = t2;
					t2 = st.top();
					st.pop();
				}
				else
				{
					sc->next();
					t1 = sc->getLastToken();
				}
			}
		}
		else if (it1 == mp.end())
		{
		    if (st.empty())
		    {
		        cout << "OP1: " << 1 << endl;
		        return true;
		    }
		    else
			{
				flag = false;
			}

		}
		if(flag == false) break;
		if(st.empty()) break;
		if(st.size() == 1)
		{
			Token tt=st.top();
			if((v_cat.find(getWord(tt))!=v_cat.end()) && (v_cat[getWord(tt)]==1))
			{
				flag = true;
				break;
			}
		}
	}
	cout << "OP2: " << flag << endl;
	return flag;
}
