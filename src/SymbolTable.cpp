#include<bits/stdc++.h>

#include <utility>
#include "SymbolTable.h"

using namespace std;

int SymbolTable::entry(string n, int t, Category c, int a) {
    return entry(SymbolTableRecord{
            std::move(n), t, c, a, false, false, false
    });
}

void SymbolTable::entryType(int id, int t) {
    table[id].type = t;
}

void SymbolTable::entryCat(int id, Category c) {
    table[id].cat = c;
}

void SymbolTable::entryAddr(int id, int a) {
    table[id].addr = a;
}

void SymbolTable::print(bool ignoreUnused) {
    cout << "====================================" << endl;
    cout << "             SymbolTable            " << endl;
    cout << "====================================" << endl;
    cout << "ID\tName\tType\tCat\tAddr" << endl;
    auto it = table.begin();
    for (int i = 0; it != table.end(); ++it, ++i) {
        if (!ignoreUnused || (it->isUsed ||
                              (!it->isUsed && it->cat == V && it->addr != -1)))
            printf("%d\t%s\t%d\t%d\t%d\n", i, it->name.c_str(),
                   it->type, it->cat, it->addr);
    }
}
