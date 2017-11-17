#ifndef OPAnalyzer_h
#define OPAnalyzer_h

#include<bits/stdc++.h>
#include "Token.h"
#include "Scanner.h"
#include "Quadruple.h"
#include "QuadrupleTable.h"
#include "TypeTable.h"
#include "utils.h"

using namespace std;

class OPAnalyzer
{
private:
    Scanner *sc;
    void init_mp();
    map<string, map<string, char> > mp;
    string getWord(Token tmp);
    string getS(Token &t1, Token &lastToken);
    stack<Token> st;
    stack<Token> tst;
    stack<Token> *sem;
    QuadrupleTable *qt;
    int tmpCnt;
    string getTmpName();
    struct cmp
    {
        bool operator()(const string &s1, const string &s2) const
        {
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
            //printf("tmps1: %s, tmps2: %s\n", tmps1.c_str(), tmps2.c_str());
            return tmps1 < tmps2;
        }
    };
    void init_g();
    map<string, string, cmp> g;
    void init_vcat();
    map<string, bool> v_cat;
    bool isEnd(string s);
    bool GEQ(char op);
    bool CALC(char op);

public:
    // If isConstDef == true, then OPAnalyzer will calculate the value
    // and save it in the sem stack
    bool E(bool isConstDef);
    OPAnalyzer(Scanner *sc, stack<Token> *sem, QuadrupleTable *qt);
};

#endif
