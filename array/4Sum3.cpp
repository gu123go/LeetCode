/*
** Author 	: Gzh
** Datetime : 1/20
** problom  : see 4Sum.cpp
*/


#include <iostream>
#include <vector>
#include <unordered_multimap>
#include <algorithm> 
using namespace std;

vector<vector<int>> Solution(vector<int> &nums, int target)
{
	vector<vector<int>> result;
	if(nums.size() < 4) return result;

	sort(nums.begin(), nums.end());
	unordered_multimap<int, pair<int, int>> cache;
	for(size_t a = 0; a < nums.size(); ++a){
		for(size_t b = a+1; b < nums.size(); ++b){
			cache.insert(make_pair(a+b, make_pair(a,b)));
		}
	}

	for(auto i = cache.begin(); i != cache.end(); ++i){
		const int x = target - i.first;
		auto range = cache.equal_range(x);
		for(auto j = range.first; j != range.second; ++j){
			auto a = i->second.first;
			auto b = i->second.second;
			auto c = j->second.first;
			auto d = j->second.second;
			if(a != c &&  != d && b != d && b != d){
				vector<int> tmpIv = {nums[a], nums[b], nums[c], nums[d]}
				sort(tmpIv.begin(), tmpIv.end());
				result.push_back(tmpIv);
			}
		}
	}
	sort(result.begin(). result.end());
	result.erase(unique(result.begin(), result.end()), result.end());
	return result;
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
