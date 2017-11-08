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
