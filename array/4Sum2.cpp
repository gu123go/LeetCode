/*
** Author 	: Gzh
** DateTime : 1/20
** Problom  : see 4Sum.cpp
** 时间复杂度 平均O(n^2) 最坏O(n^4) 空间复杂度O(n^2)
** solution 3 please go to 4Sum3.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

std::vector<std::vector<int>> Solution(std::vector<int> &nums, int target)
{
	std::vector<std::vector<int>> result;
	if(nums.size() < 4) return result;

	sort(nums.begin(), nums.end());
	unordered_map<int, vector<pair<int, int>>> cache;
	for(size_t a = 0; a < nums.size(); ++a){
		for(size_t b = a+1; b < nums.size(); ++b){
			cache[nums[a]+nums[b]].push_back(pair<int, int>(a, b));
		}
	}
	for(int c = 0; c < nums.size(); ++c){
		for(int d = c+1; d < nums.size(); ++d){
			const int key = target - nums[c] - nums[d];
			if(cache.find(key) == cache.end()) continue;

			const auto& vec = cache[key];
			for(size_t k = 0; k < vec.size(); ++k){
				if(c <= vec[k].second)
					continue;         //重叠
				result.push_back({nums[vec[k].first], nums[vec[k].second], nums[c], nums[d]});
			}
		}
	}
	sort(result.begin(), result.end());
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