/*
** Author 	: Gzh
** Datetime : 1/20
** Problom  : 输出所给字符串的全排列（递归实现）
** solution 2 please go to permutation2.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
inline void swap(T *a, T *b)
{
	T c;
	c = *a;
	*a = *b;
	*b = c;
}

template<typename T>
void AllRange(vector<T> &vecs, int k, int m)
{
	if(k == m){
		static int index = 1;
		cout << "第" << index++ << "个：";
		for(auto item : vecs)
			cout << item;
		cout << endl;
	}
	else{
		for(int i = k; i <= m; ++i){
			if(find(vecs.begin()+k, vecs.begin()+i, vecs[i]) == vecs.begin()+i){ //处理有重复的数字
				swap(vecs[k], vecs[i]);
				AllRange(vecs, k+1, m); 
				swap(vecs[k], vecs[i]);
			}
		}
	}
}


int main()
{
	vector<int> iv{1,2,2};
	AllRange(iv, 0, iv.size()-1);
	return 0;
}