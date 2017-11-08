#ifndef SYMBOLTABLERECORD_H
#define SYMBOLTABLERECORD_H

#include<string>
#include<vector>
#include "Category.h"
using namespace std;

struct SymbolTableRecord
{
	string name;
	int type;
	Category cat;
	int addr;
};

typedef vector<SymbolTableRecord> SymbolTable;

#endif
