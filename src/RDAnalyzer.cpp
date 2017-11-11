#include<bits/stdc++.h>
#include "RDAnalyzer.h"
#include "Token.h"

using namespace std;

RDAnalyzer::RDAnalyzer(Scanner *sc) : sc(sc), opa(sc){}

bool RDAnalyzer::analyze()
{
	return PG();
}

bool RDAnalyzer::PG()
{
	bool flag = true;
	do{
		if(!ST())
		{
			flag = false;
			break;
		}
	}while(true);
	return flag;
}

bool RDAnalyzer::ST()
{
	Token tmp = sc->getLastToken();
	if(tmp.type == IDENTIFIER)
	{
		sc->next();
		tmp = sc->getLastToken();
		if(tmp.word == "=")
		{
			sc->next();
			return opa.E();
		}
		else return false;
	}
	else return (VD()&&TP()&&IT());
}

bool RDAnalyzer::VD()
{
	Token tmp = sc->getLastToken();
	if((tmp.type == KEYWORD) && (tmp.word == "const"))
		sc->next();
	return true;
}

bool RDAnalyzer::TP()
{
	Token tmp = sc->getLastToken();
	if((tmp.type == KEYWORD) && ((tmp.word == "int") || (tmp.word == "float")))
	{
		sc->next();
		return true;
	}
	return false;
}

bool RDAnalyzer::IT()
{
	if(IFD())
	{
		bool flag = true;
		while(true)
		{
			Token tmp = sc->getLastToken();
			if((tmp.type == DELIMITER) && (tmp.word == ","))
			{
				sc->next();
				if(!IT())
					flag = false;
			}
			else flag = false;
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
