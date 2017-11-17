#include<bits/stdc++.h>
#include "TypeTable.h"

using namespace std;

int TypeTable::entry(Tval tv, int tp)
{
    return entry((TypeTableRecord)
    {
        tv,tp
    });
}

TypeTable::TypeTable()
{
    entry(INTEGER, -1);
    entry(FLOAT, -1);
    entry(CHAR, -1);
    entry(STRING, -1);
}
