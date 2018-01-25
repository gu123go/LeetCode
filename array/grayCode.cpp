/*
** Author 	 : Gzh
** Datetime  : 1/24
** Problom   : Gray Code [格雷码 (Gray Code) 的定义请参考 http://en.wikipedia.org/wiki/Gray_code]
** Solution 2 please go to grayCode2.cpp
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
auto Solution(int n) -> vector<int>
{
	vector<int> result;
	const size_t size = 1 << n;
	result.reserve(size);

	for(size_t i = 0; i < size; ++i)
		result.push_back(i^(i >> 1));

	return result;
}

int main()
{
	auto iv = Solution(4);
	for(auto item : iv)
		cout << item << "\t";
	cout << endl;

	return 0;
}