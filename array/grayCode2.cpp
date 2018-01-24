/*
** Author 	: Gzh
** Datetime : 1/24
** Problom  : see grayCode.cpp
*/


#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

auto Solution(int n)
	-> vector<int>
{
	vector<int> result;
	const size_t size = 1 << n;
	result.reserve(size);
	result.push_back(0);
	for(int i = 0; i < n; ++i){
		const int hight_bit = 1 << i;
		for(int j = result.size()-1; j >= 0; --j)
			result.push_back(hight_bit | result[j]);           
	}

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
