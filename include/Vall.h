#ifndef VALL_H
#define VALL_H

#include<vector>
using namespace std;

struct VallRecord
{
	int offset;
};

struct Vall
{
	vector<VallRecord> v;
	int totoffset;
};

#endif
