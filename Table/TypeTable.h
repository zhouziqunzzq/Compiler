#ifndef TYPETABLE_H
#define TYPETABLE_H

#include<vector>
using namespace std;

enum Tval
{
	INTEGER = 1,
	FLOAT = 2
};

struct TypeTableRecord
{
	Tval tval;
	int tptr;
};

typedef vector<TypeTableRecord> TypeTable;

#endif
