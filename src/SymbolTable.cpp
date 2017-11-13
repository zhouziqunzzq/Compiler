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

