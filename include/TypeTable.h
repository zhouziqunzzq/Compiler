#ifndef TYPETABLE_H
#define TYPETABLE_H

#include "Table.h"

using namespace std;

enum Tval {
    INTEGER = 1,
    FLOAT = 2,
    CHAR = 3,
    STRING = 4
};

struct TypeTableRecord {
    Tval tval;
    int tptr;

    friend bool operator<(const TypeTableRecord &ls, const TypeTableRecord &rs) {
        return ls.tval < rs.tval;
    }
};

class TypeTable : public Table<TypeTableRecord> {
public:
    TypeTable();

    using Table<TypeTableRecord>::entry;

    int entry(Tval tv, int tp);
};

#endif
