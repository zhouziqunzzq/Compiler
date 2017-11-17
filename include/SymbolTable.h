#ifndef SYMBOLTABLERECORD_H
#define SYMBOLTABLERECORD_H

#include<string>
#include "Category.h"
#include "Table.h"
using namespace std;

struct SymbolTableRecord
{
	string name;
	int type;
	Category cat;
	int addr;   // addr = -1 means temp

	friend bool operator<(const SymbolTableRecord &ls, const SymbolTableRecord &rs)
	{
	    return ls.name < rs.name;
	}
};

class SymbolTable : public Table<SymbolTableRecord>
{
public:
    using Table<SymbolTableRecord>::entry;
    int entry(string n, int t, Category c, int a);
    void entryType(int id, int t);
    void entryCat(int id, Category c);
    void entryAddr(int id, int a);
    void print();
};

#endif
