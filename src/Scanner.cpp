#include<bits/stdc++.h>
#include "Scanner.h"

using namespace std;

Scanner::Scanner(string s) : content(s)
{
    //ctor
}

void Scanner::reset()
{
    buffer.clear();
    curState = 1;
}

void Scanner::rewind()
{
    --curIndex;
    buffer.erase(buffer.end() - 1);
}

void Scanner::next()
{
    //
}
