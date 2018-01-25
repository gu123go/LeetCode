/*
** Author 	: Gzh
** DateTime : 1/20
** Problom  : Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target?
			  Find all unique quadruplets in the array which gives the sum of target.
			  Note:
			  • Elements in a quadruplet (a, b, c, d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
			  • The solution set must not contain duplicate quadruplets.
			  For example, given array S = {1 0 -1 0 -2 2}, and target = 0.
				A solution set is:
				(-1, 0, 0, 1)
				(-2, -1, 1, 2)
				(-2, 0, 0, 2)
** O(n^3)
** solution 2 please go to 4Sum2.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> Solution(vector<int> &nums, int target)
{
	std::vector<std::vector<int>> res;
	if(nums.size() < 4) return res;

	sort(nums.begin(), nums.end());

	auto last = nums.end();
	for(auto a = nums.begin(); a < last-3; ++a){
		for(auto b = a+1; b < last-2; ++b){
			auto c = b+1;
			auto d = last-1;
			while(c < d){
				if(*a + *b + *c + *d < target){
					++c;
				} 
				else if(*a + *b + *c + *d > target){
					--d;
				}
				else{
					res.push_back({*a, *b, *c, *d});
					++c;
					--d;
				}
			}
		}
	}
	sort(res.begin(), res.end());
	res.erase(unique(res.begin(), res.end()), res.end());
	return res;
}

int main()
{
	vector<int> iv{1, 0, -1, 0, -2, 2};

	vector<vector<int>> result = Solution(iv, 0);
	for (auto &ivs : result){
		for(auto item : ivs){
			cout << item << "\t";
		}
		cout << endl;
	}

	return 0;
}