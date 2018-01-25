/*
** Author   : Gzh
** Datetime : 1/6
** Problom  : Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
			  For example, Given [100, 4, 200, 1, 3, 2], The longest consecutive elements sequence is [1,
			  2, 3, 4]. Return its length: 4.
			  Your algorithm should run in O(n) complexity
** 时间复杂度O(n)；空间复杂度O(n)
** solution 2 please go to longestConsecutiveSeq2 
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int Solution(const vector<int> &nums, int *start)
{
	int longest = 0;
	unordered_map<int, bool> used;
	for(auto item : nums) used[item] = false;
	

	for(auto item : nums){
		if(used[item]) continue;
		
		int ans = 1;
		
		int j;
		for(j = item+1; used.find(j) != used.end(); ++j){
			used[j] = true;
			++ans;
		}
		
		for(j = item-1; used.find(j) != used.end(); --j){
			used[j] = true;
			++ans; 
		}
		longest = max(longest, ans);
		*start = longest == ans ?  ++j : *start;
	}
	return longest;
}

int main()
{
	vector<int> iv{100, 4, 200, 1, 3, 2};
	int start;
	cout << Solution(iv, &start);
	cout << "\t" <<start << endl;
	return 0;
}
	
 
