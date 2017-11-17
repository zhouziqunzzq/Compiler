#include<bits/stdc++.h>
#include "RDAnalyzer.h"
#include "Token.h"
#include "Vall.h"

using namespace std;

RDAnalyzer::RDAnalyzer(Scanner *sc, QuadrupleTable *qt) : sc(sc), qt(qt), opa(sc, &sem, qt){}

bool RDAnalyzer::analyze()
{
    sc->next();
    return PG();
}

bool RDAnalyzer::PG()
{
    do
    {
        if(!ST())
        {
            return false;
        }
    }
    while(sc->getLastToken().type != END);
    return true;
}

void RDAnalyzer::ASSI()
{
    cout << "ASSI" << endl;
    Quadruple qd(ASSIGN, sem.top().id, -1, lastIdentifier.id);
    qt->push_back(qd);
    sem.pop();
}

bool RDAnalyzer::ST()
{
	entloop = 0;
    constflag = 0;
    constintflag = 0;
    constfloatflag = 0;
    intflag = 0;
    floatflag = 0;
	Token tmp = sc->getLastToken();
	if(tmp.type == IDENTIFIER)
	{
	    lastIdentifier = tmp;
		sc->next();
		tmp = sc->getLastToken();
		if(tmp.word == "=")
		{
			sc->next();
			if (opa.E())
            {
                ASSI();
                if (sc->getLastToken().type == DELIMITER &&
                    sc->getLastToken().word == ";")
                {
                    sc->next();
                    return true;
                }
                else return false;
            }
            else return false;
		}
		else return false;
	}
	else
    {
        if (!(VD()&&TP()&&IT()))
            return false;
        if (sc->getLastToken().type == DELIMITER &&
            sc->getLastToken().word == ";")
        {
            sc->next();
            return true;
        }
        else
            return false;
    }
}

bool RDAnalyzer::VD()
{
    Token tmp = sc->getLastToken();
    if((tmp.type == KEYWORD) && (tmp.word == "const"))
    {
        constflag = 1;
        sc->next();
    }
    return true;
}

void RDAnalyzer::Typ(Token tmp)
{
    if(tmp.word =="int")
    {
        intflag = 1;
        if(constflag == 1)
            constintflag = 1;
    }
    else
    {
        floatflag = 1;
        if(constflag == 1)
            constfloatflag = 1;
    }
}

bool RDAnalyzer::TP()
{
    Token tmp = sc->getLastToken();
    if((tmp.type == KEYWORD) && ((tmp.word == "int") || (tmp.word == "float")))
    {
        Typ(tmp);
        sc->next();
        return true;
    }
    return false;
}

void RDAnalyzer::Ent()
{
    if(intflag == 1)
    {
        sc->st->entryType(sc->getLastToken().id,1);
        VallRecord r;
        r.offset = sc->vall->totoffset;
        sc->vall->v.push_back(r);
        sc->vall->totoffset += INTSIZE;
        sc->st->entryAddr(sc->getLastToken().id,r.offset);
        if(constintflag == 1)
            sc->st->entryCat(sc->getLastToken().id,C);
        else
            sc->st->entryCat(sc->getLastToken().id,V);

        sc->st->print();
    }
    else if(floatflag == 1)
    {
        sc->st->entryType(sc->getLastToken().id,2);
        VallRecord r;
        r.offset = sc->vall->totoffset;
        sc->vall->v.push_back(r);
        sc->vall->totoffset += FLOATSIZE;
        sc->st->entryAddr(sc->getLastToken().id, r.offset);
        if(constfloatflag == 1)
            sc->st->entryCat(sc->getLastToken().id,C);
        else
            sc->st->entryCat(sc->getLastToken().id,V);

        sc->st->print();
    }
}

bool RDAnalyzer::IT()
{
    if(IFD())
    {
        bool flag = true;
        while(true)
        {
            ASSI();
            Token tmp = sc->getLastToken();
            if((tmp.type == DELIMITER) && (tmp.word == ","))
            {
                sc->next();
                if(!IT())
                    flag = false;
            }
            else break;
            if(flag == false) break;
        }
        return flag;
    }
    else return false;
}

bool RDAnalyzer::IFD()
{
    if(PD())
    {
        Token tmp = sc->getLastToken();
        if(tmp.type == IDENTIFIER)
        {
            lastIdentifier = tmp;
            Ent();
            sc->next();
            if(IS())
                return true;
            else
                return false;
        }
        else return false;
    }
    else return false;
}

bool RDAnalyzer::PD()
{
    Token tmp = sc->getLastToken();
    if((tmp.type == DELIMITER) && (tmp.word == "*"))
        sc->next();
    return true;
}

bool RDAnalyzer::IS()
{
	Token tmp = sc->getLastToken();
	if((tmp.type == DELIMITER) && (tmp.word == "="))
	{
		sc->next();
		return opa.E();
	}
	return true;
}
