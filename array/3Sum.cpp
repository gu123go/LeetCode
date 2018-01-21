/*
** Author   : Gzh
** Datetime : 1/6
** Problom  : Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique
			  triplets in the array which gives the sum of zero.
			  Note:
			  ? Elements in a triplet (a, b, c) must be in non-descending order. (ie, a ¡Ü b ¡Ü c)
			  ? The solution set must not contain duplicate triplets.
			  For example, given array S = {-1 0 1 2 -1 -4}.
			  A solution set is:
			  (-1, 0, 1)
			  (-1, -1, 2)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> Solution(vector<int> &nums, const int target)
{
	vector<vector<int>> res; 
	sort(nums.begin(), nums.end());
	for(int i = 0; i < nums.size()-2; ++i){
		if(i != 0 && nums[i]==nums[i-1]) continue;
		int tmp = target - nums[i];
		int s = i+1;
		int e = nums.size()-1;
		while(s < e){
			if(nums[s] + nums[e] == tmp){
				res.push_back({nums[i], nums[s], nums[e]});
				++s, --e;
			}
			else if(nums[s] + nums[e] > tmp) --e;
			else ++s;
		}
	}
	return res;
}

int main()
{
	vector<int> iv{-1, 0, 1, 2, -1, -4};
	vector<vector<int>> res = Solution(iv, 0);
	for(auto &ivs : res){
		for(auto item : ivs){
			cout << item << "\t";
		}
		cout << endl;
	}
	return 0;
}


