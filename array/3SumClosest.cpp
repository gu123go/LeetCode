/*
** Author   : Gzh
** Datetime : 1/20
** Problom  : Given an array S of n integers, find three integers in S such that the sum is closest to a given number,
			  target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
			  For example, given array S = {-1 2 1 -4}, and target = 1.
			  The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int Solution(vector<int> nums, int target)
{
	//sort first
	sort(nums.begin(), nums.end());

	int result, min_gap = INT_MAX;
	for(int i = 0; i < nums.size()-2; ++i){
		size_t s = i+1, e = nums.size()-1;
		while(s < e){
			const int sum = nums[i] + nums[s] + nums[e];
			const int gap = abs(target - sum);
			if(gap < min_gap){
				result = sum;
				min_gap = gap;
			}

			if(target < sum) ++s;
			else --e;
		}
	}
	return result;

}

int main()
{
	vector<int> iv{-1,2,1,-4};
	cout << Solution(iv, 1) << endl;
	return 0;
}
