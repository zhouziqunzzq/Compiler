#include<bits/stdc++.h>
#include "SymbolTable.h"

using namespace std;

int SymbolTable::entry(string n, int t, Category c, int a)
{
    return entry((SymbolTableRecord)
    {
        n, t, c, a
    });
}

void SymbolTable::entryType(int id, int t)
{
    table[id].type = t;
}

void SymbolTable::entryCat(int id, Category c)
{
    table[id].cat = c;
}

void SymbolTable::entryAddr(int id, int a)
{
    table[id].addr = a;
}

void SymbolTable::print()
{
    cout << "============================" << endl;
    cout << "         SymbolTable        " << endl;
    cout << "============================" << endl;
    cout << "Name\tType\tCat\tAddr" << endl;
    auto it = table.begin();
    for (; it != table.end(); ++it)
        printf("%s\t%d\t%d\t%d\n", it->name.c_str(),
               it->type, it->cat, it->addr);
}
