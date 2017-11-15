#include<bits/stdc++.h>
#include "OPAnalyzer.h"
#define isVN(t) v_cat.find(getWord((t))) == v_cat.end()
#define isVT(t) v_cat.find(getWord((t))) != v_cat.end()

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

string OPAnalyzer::getS(Token &t1)
{
    Token tmp;
    //st.pop();
    //printf("tmp: %s\n", getWord(tmp).c_str());
    Token tmptst = t1;
    string res;
    while(!tst.empty() && mp[getWord(tst.top())][getWord(tmptst)] != '<')
    {
        tmp = st.top();
        //st.pop();
        res = getWord(tmp) + res;
        if (isVT(tmp) && tmp == tst.top())
        {
            tmptst = tst.top();
            tst.pop();
        }
        st.pop();
        if(st.empty()) break;
    }
    // Pop out remaining VN in st
    while (!st.empty() && (isVN(st.top()) ||
            getWord(st.top()) != getWord(tst.top())))
    {
        res = getWord(st.top()) + res;
        st.pop();
    }
    return res;
}

bool OPAnalyzer::E()
{
    while (!st.empty())
        st.pop();
    while (!tst.empty())
        tst.pop();
    // st: Analyze stack
    // tst: Analyze stack with only VT in it
    // flag: The result of OPAnalyzation
    // f2: Whether Scanner reaches the end of an Expression
    bool flag = true, f2 = false;
    // t1: Current token to be analyzed given by Scanner
    Token t1 = sc->getLastToken();
    // t2: The top of st
    Token t2;
    // vst: The top of tst
    Token vst;
    // Initialize st, tst, t1
    if (isEnd(getWord(t1)))  // Special judge for empty expression
        return false;
    printf("Pushing %s into st and moving on...\n", getWord(t1).c_str());
    st.push(t1);
    if (isVT(t1))
        tst.push(t1);
    sc->next();
    t1 = sc->getLastToken();
    while(true)
    {
        t2 = st.top();
        //st.pop();
        //printf("1. t1: %s, t2: %s\n", t1.word.c_str(), t2.word.c_str());
        if(!f2 && isEnd(getWord(t1)))
            f2 = true;
        /*if(!f2 && isVN(t2))
        {
            printf("t1: %s, t2: %s\n", t1.word.c_str(), t2.word.c_str());
            printf("getWord(t1): %s, getWord(t2): %s\n", getWord(t1).c_str(), getWord(t2).c_str());
            st.push(t1);
            if (v_cat.find(getWord(t1)) != v_cat.end())
                tst.push(t1);
            sc->next();
            t1 = sc->getLastToken();
            continue;
        }*/
        map<string, map<string, char> >::iterator it2;
        map<string, char>::iterator it1;
        if (!tst.empty())
        {
            vst = tst.top();
            it2 = mp.find(getWord(vst));
        }
        if (tst.empty() || it2 != mp.end())
        {
            if (!tst.empty())
            {
                it1 = mp[getWord(vst)].find(getWord(t1));
                //printf("2. t1: %s, t2: %s, vst: %s\n", t1.word.c_str(), t2.word.c_str(), vst.word.c_str());
            }
            if (f2 || tst.empty() || it1 != mp[getWord(vst)].end())
            {
                if(f2 || (!tst.empty() && mp[getWord(vst)][getWord(t1)] == '>'))
                {
                    printf("Performing reduction...\n");
                    string stmp = getS(t1);
                    //printf("stmp: %s\n", stmp.c_str());
                    //printf("tst: %s\n", tst.empty() ? "empty" : getWord(tst.top()).c_str());
                    auto ts = g.find(stmp);
                    if(ts != g.end())
                    {
                        Token to(KEYWORD, g[stmp], -1);
                        printf("g[stmp]: %s\n", g[stmp].c_str());
                        st.push(to);
                        //printf("st.top: %s\n", getWord(st.top()).c_str());
                    }
                    else flag = false;
                }
                else
                {
                    printf("Pushing %s into st and moving on...\n", getWord(t1).c_str());
                    st.push(t1);
                    if (isVT(t1))
                        tst.push(t1);
                    sc->next();
                    t1 = sc->getLastToken();
                }
            }
            else
                flag = false;
        }
        else
            flag = false;
        if(flag == false) break;
        if(st.empty()) break;
        if(f2 && st.size() == 1)
        {
            Token tt=st.top();
            printf("getWord(tt): %s\n", getWord(tt).c_str());
            if (isVN(tt))
            {
                flag = true;
                break;
            }
        }
        //printf("3. t1: %s, t2: %s, st.top: %s\n", t1.word.c_str(), t2.word.c_str(), getWord(st.top()).c_str());
        //st.pop();
    }
    printf("OPAnalyzer::flag = %d\n", flag);
    return flag;
}
