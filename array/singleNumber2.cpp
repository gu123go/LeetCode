/*
** Author 	: Gzh
** Datetime : 1/25
** Problom  : Given an array of integers, every element appears three times except for one. Find that single one.
				Note: Your algorithm should have a linear runtime complexity. Could you implement it without using
				extra memory?
**时间复杂度O(n), 空间复杂度O(1)
*/

#include <iostream>
#include <vector>

using namespace std;

int Solution1(const vector<int> &nums)
{
	const int size = sizeof(int) * 8;
	int count[size];

	fill_n(count, size, 0);

	for(int i = 0; i < nums.size(); ++i){
		for(int j = 0; j < size; ++j){
			count[j] += (nums[i] >> j) & 0x01;
			count[j] %= 3;
		}
	}
	int result = 0;
	for(int i = 0; i < size; ++i){
		result += (count[i] << i);
	}

	return result;
}

//???
/*
int Solution2(const vector<int> &nums)
{
	int one = 0, two = 0, three = 0;
	for(auto i : nums){
		two |= (one & i);
		one ^= i;
		three = ~(one & two);
		one &= three;
		two &= three;

		cout << one << "\t" << two << "\t" << three << endl;
	}

	return one;
}
*/

int main()
{

	vector<int> iv{1,1,1,2,2,3,2,4,4,4};
	cout << Solution2(iv) << endl;

	return 0;
}