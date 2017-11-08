#ifndef KEYWORDTABLE
#define KEYWORDTABLE

#include<string>
#include "Table.h"
using namespace std;

typedef Table<string> KeywordTable;

void fillKT(KeywordTable *kt)
{
	kt->fill("const");
	kt->fill("int");
	kt->fill("float");
}

#endif
