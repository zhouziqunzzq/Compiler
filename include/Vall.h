#ifndef VALL_H
#define VALL_H

#include<vector>

using namespace std;

const int INTSIZE = 4;
const int FLOATSIZE = 4;

struct VallRecord {
    int offset;
};

struct Vall {
    vector<VallRecord> v;
    int totoffset;

    Vall() {
        totoffset = 0;
    }
};

#endif
