#ifndef DELIMITERTABLE
#define DELIMITERTABLE

#include<string>
#include "Table.h"

using namespace std;

class DelimiterTable : public Table<string> {
public:
    DelimiterTable();
};

#endif
