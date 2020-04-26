#include<bits/stdc++.h>
#include "StateChangeTable.h"

using namespace std;

StateChangeTable::StateChangeTable() {
    // Node 1
    table[1]['\n'] = table[1]['\r'] = table[1]['\t'] = table[1][' '] = 1;
    table[1]['\''] = 5;
    table[1]['\"'] = 8;
    table[1]['/'] = 20;
    table[1]['#'] = 21;
    fillAlphabet(1, 2);
    table[1]['_'] = 2;
    fillNumber(1, 3);
    fillSingleDelimiter(1, 11);
    fillDoubleDelimiter(1, 18);
    // Node 2
    fillAll(2, 12);
    fillAlphabet(2, 2);
    fillNumber(2, 2);
    table[2]['_'] = 2;
    // Node 3
    fillAll(3, 14);
    fillNumber(3, 3);
    table[3]['.'] = 4;
    table[3]['e'] = 26;
    // Node 4
    fillAll(4, 13);
    fillNumber(4, 4);
    table[4]['e'] = 26;
    // Node 5
    fillAll(5, 6);
    table[5]['\''] = 7;
    // Node 6
    table[6]['\''] = 7;
    // Node 7
    fillAll(7, 15);
    // Node 8
    fillAll(8, 9);
    table[8]['"'] = 10;
    // Node 9
    fillAll(9, 9);
    table[9]['"'] = 10;
    // Node 10
    fillAll(10, 16);
    // Node 11
    fillAll(11, 17);
    // Node 18
    fillAll(18, 19);
    fillDoubleDelimiter(18, 18);
    // Node 20
    fillAll(20, 17);
    table[20]['/'] = 21;
    table[20]['*'] = 23;
    // Node 21
    fillAll(21, 21);
    table[21]['\n'] = 22;
    // Node 23
    fillAll(23, 23);
    table[23]['/'] = 25;
    // Node 26
    fillNumber(26, 27);
    table[26]['-'] = 27;
    // Node 27
    fillAll(27, 28);
    fillNumber(27, 27);
}

bool StateChangeTable::hasNextState(int curState, char curChar) {
    return table[curState].find(curChar) != table[curState].end();
}

int StateChangeTable::getNextState(int curState, char curChar) {
    return table[curState][curChar];
}

void StateChangeTable::fillAlphabet(int s, int i) {
    for (int j = 'a'; j <= 'z'; ++j)
        table[s][char(j)] = i;
    for (int j = 'A'; j <= 'Z'; ++j)
        table[s][char(j)] = i;
}

void StateChangeTable::fillNumber(int s, int i) {
    for (int j = '0'; j <= '9'; ++j)
        table[s][char(j)] = i;
}

void StateChangeTable::fillSingleDelimiter(int s, int i) {
    const int MAXD = 12;
    char d[MAXD] = {'+', '-', '*', ',', '.', '(', ')', '[', ']', '{', '}', ';'};
    for (int j = 0; j < MAXD; ++j)
        table[s][d[j]] = i;
}

void StateChangeTable::fillDoubleDelimiter(int s, int i) {
    const int MAXD = 6;
    char d[MAXD] = {'>', '<', '=', '!', '&', '|'};
    for (int j = 0; j < MAXD; ++j)
        table[s][d[j]] = i;
}

void StateChangeTable::fillAll(int s, int i) {
    for (int j = 0; j < 256; ++j)
        table[s][char(j)] = i;
}
