/*
** Author 	: Gzh
** Datetime : 1/22
** Problom  : see rapRainWater.cpp
** 时间复杂度O(n), 空间复杂度O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(const vector<int> &A)
{
	const int n = A.size();
	int max = 0;        //最高的柱子，将数组分成两组

	for(int i = 0; i < n; ++i){
		if(A[i] > A[max]) max = i;       
	}

	int peek = A[0], sum = 0;
	for(int i = 1; i < max; ++i){
		if(peek > A[i]) sum += peek - A[i];
		else peek = A[i];
	}

	peek = A[n-1];
	for(int i = n-2; i > max; --i){
		if(peek > A[i]) sum += peek - A[i];
		else peek = A[i];
	}
	return sum;
}


int main()
{
	vector<int> iv{0,1,0,2,1,0,1,3,2,1,2,1};
	cout << Solution(iv) << endl;
	return 0;
}
