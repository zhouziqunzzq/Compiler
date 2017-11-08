#ifndef KEYWORDTABLE
#define KEYWORDTABLE

#include<string>
#include "Table.h"
using namespace std;

class KeywordTable : public Table<string>
{
public:
    KeywordTable();
};

#endif
