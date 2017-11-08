#ifndef TABLE_H
#define TABLE_H

#include<vector>
#include<map>
using namespace std;

template<class T>
class Table
{
	private:
		vector<T> table;
		map<T, int> index;
	
	public:
		int fill(T v);
		bool get(int id, T &v);
};

template<class T>
int Table<T>::fill(T v)
{
	auto it = index.find(v);
	if(it != index.end())
		return it->second;
	else
	{
		table.push_back(v);
		index[v]=table.size();
		return table.size()-1;
	}
}

template<class T>
bool Table<T>::get(int id, T &v)
{
	if(id >= table.size())
		return false;
	else
	{
		v = table[id];
		return true;
	}
}

#endif
