/*
** Author   : Gzh
** Datetime : 1/22
** Problom  : Given n non-negative integers representing an elevation map where the width of each bar is 1, compute
				how much water it is able to trap after raining.
				For example, Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
** 时间复杂度O(n), 空间复杂度O(n)
** solution 2 please goto trapRainWater2.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

int Solution(const vector<int> &A)
{
	const int n = A.size();
	int *max_left = new int[n];
	int *max_right = new int[n];

	memset(max_left, 0, sizeof(int)*n);
	memset(max_right, 0, sizeof(int)*n);

	for(int i = 1; i < n; ++i){
		max_left[i] = max(A[i-1], max_left[i-1]);
		max_right[n-i-1] = max(A[n-i], max_right[n-i]);
	}


	int sum = 0;
	for(int i = 0; i < n; ++i){
		int height = min(max_right[i], max_left[i]);
		if(height > A[i])
			sum += height - A[i];
	}

	delete[] max_right;
	delete[] max_left;
	
	return sum;
}

int main()
{

	vector<int> iv{0,1,0,2,1,0,1,3,2,1,2,1};
	cout << Solution(iv);
	return 0;
}