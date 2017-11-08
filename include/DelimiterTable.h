#ifndef DELIMITERTABLE
#define DELIMITERTABLE

#include<string>
#include "Table.h"
using namespace std;

typedef Table<string> DelimiterTable;

void fillDT(DelimiterTable *dt)
{
	dt->fill("+");
	dt->fill("-");
	dt->fill("*");
	dt->fill("/");
	dt->fill("(");
	dt->fill(")");
	dt->fill(",");
	dt->fill(";");
	dt->fill("=");
}

#endif
