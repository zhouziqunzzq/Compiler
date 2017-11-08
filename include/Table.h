#ifndef TABLE_H
#define TABLE_H

#include<vector>
#include<map>
using namespace std;

template<class T>
class Table
{
protected:
    vector<T> table;
    map<T, int> index;

public:
    int entry(T v);
    T getValue(int id);
    int getID(T v);
    bool has(T v);
};

template<class T>
int Table<T>::entry(T v)
{
    auto it = index.find(v);
    if(it != index.end())
        return it->second;
    else
    {
        table.push_back(v);
        index[v]=table.size()-1;
        return table.size()-1;
    }
}

template<class T>
T Table<T>::getValue(int id)
{
    return table[id];
}

template<class T>
int Table<T>::getID(T v)
{
    return index[v];
}

template<class T>
bool Table<T>::has(T v)
{
    return index.find(v) != index.end();
}

#endif
