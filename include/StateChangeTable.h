#ifndef STATECHANGETABLE_H
#define STATECHANGETABLE_H

#include <map>

using namespace std;

const int MAXSTATE = 40;

class StateChangeTable {
public:
    StateChangeTable();

    bool hasNextState(int curState, char curChar);

    int getNextState(int curState, char curChar);

protected:

private:
    map<char, int> table[MAXSTATE];

    void fillAlphabet(int s, int i);

    void fillNumber(int s, int i);

    void fillSingleDelimiter(int s, int i);

    void fillDoubleDelimiter(int s, int i);

    void fillAll(int s, int i);
};

#endif // STATECHANGETABLE_H
