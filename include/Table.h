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
    const T& getValue(int id) const;
    int getID(T v);
    bool has(T v);
    void print(string name);
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
const T& Table<T>::getValue(int id) const
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

template <class T>
void Table<T>::print(string name)
{
    cout << "====================================" << endl;
    cout << "        " << name << "              " << endl;
    cout << "====================================" << endl;
    cout << "ID\tValue" << endl;
    auto it = table.begin();
    for (int i = 0; it != table.end(); ++it, ++i)
        cout << i << "\t" << *it << endl;
}

#endif
