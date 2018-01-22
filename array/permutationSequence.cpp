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
#include <string>

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




int factorial(int n)
{
	int result = 1;
	for (int i = 1; i <= n; ++i)
	{
		result *= i;
	}
	return result;
}

template<typename Sequence>
Sequence kth_permutation(const Sequence &seq, int k)
{
	const int n = seq.size();
	Sequence S(seq);
	Sequence result;

	int base = factorial(n-1);
	--k;

	for(int i = n-1; i > 0; k %= base, base /= i, --i){
		cout << k << "\t" << base <<endl;
		auto a = next(S.begin(), k/base);
		result.push_back(*a);
		S.erase(a);
	}

	result.push_back(S[0]);
	return result;
}

//get kth of n numbers(1...n; 1 <= n <= 9)
string getPermutation(int n, int k)
{
	string s(n, '0');
	string result;
	for(int i = 0; i < n; ++i)
		s[i] += i+1;

	return kth_permutation(s, k);
}

int main()
{
	cout << getPermutation(5, 5) << endl;
	return 0;
}