/*
** Author 	: Gzh
** Datetime : 1/25
** Problom  : Given an array of integers, every element appears twice except for one. Find that single one.
				Note: Your algorithm should have a linear runtime complexity. Could you implement it without using
				extra memory?
*/

#include <iostream>
#include <vector>

using namespace std;

int Solution(const vector<int> &nums)
{
	int result = nums[0];
	for(int i = 1; i < nums.size(); ++i){
		result ^= nums[i];
	}
	//return accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
	return result;
}

int main()
{

	vector<int> iv{1,2,3,4,5,1,2,5,4,3,0};
	cout << Solution(iv) << endl;

	return 0;
}
