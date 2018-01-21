/*
** Author   : Gzh
** Datetime : 1/6
** Problom  : Given an array of integers, find two numbers such that they add up to a specific target number.
			  The function twoSum should return indices of the two numbers such that they add up to the target, where
			  index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not
			  zero-based.
			  You may assume that each input would have exactly one solution.
			  Input: numbers={2, 7, 11, 15}, target=9
			  Output: index1=1, index2=2
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std; 

vector<int> Solution(const vector<int> &nums, const int sum)
{
	vector<int> res;
	unordered_map<int, int> map;
	for(int i = 0; i < nums.size(); ++i){
		const int gap = sum - nums[i];
		if(map.find(gap) != map.end()){
			if(map[gap] < i+1){
				res.push_back(map[gap]);
				res.push_back(i+1);
			}else{
				res.push_back(i+1);
				res.push_back(map[gap]);
			}
			break;
		}else{
			map[nums[i]] = i+1; 
		}
	}
	
	return res;
}

int main()
{
	vector<int> iv{2, 7, 11, 15};
	int sum = 9;
	vector<int> res = Solution(iv, sum);
	for(auto item : res)
		cout << item << "\t";
	cout << endl;
	return 0;
}
