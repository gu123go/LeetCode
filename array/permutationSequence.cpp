/*
** Author 	 : Gzh
** Datetime  : 1/21
** Problom   : The set [1,2,3,ĉ ,n] contains a total of n! unique permutations.
				By listing and labeling all of the permutations in order, We get the following sequence (ie, for n = 3):
					"123"
					"132"
					"213"
					"231"
					"312"
					"321"
				Given n and k, return the kth permutation sequence.
				Note: Given n will be between 1 and 9 inclusive.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//暴力求解
/*
string Solution(int n, int k)
{
	string str(n, '0');
	for(int i = 0; i < n; ++i){
		str[i] += i+1;
	}
	for(int i = 0; i < k-1; ++i)
		next_permutation(str.begin(), str.end());
	return str;
}
*/

//康托编码
//时间复杂度 O(n), 空间复杂度 O(1)



int main()
{
	return 0;
}