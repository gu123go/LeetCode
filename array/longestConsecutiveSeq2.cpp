/*
** Author   : Gzh
** Datetime : 1/6
** Problom  : ¼û longestConsecutiveSeq.cpp ÎÄ¼þ
*/
 
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int mergeCluster(unordered_map<int, int> &map, int left, int right)
{
	int upper = right + map[right] - 1;
	int lower = left - map[left] + 1;
	int length = upper - lower + 1;
	map[upper] = length;
	map[lower] = length;
	return length;	
}

int Soluciont(const vector<int> &nums)
{
	unordered_map<int, int> map;
	int longest = 0;
	
	for(auto item : nums){
		if(map.find(item) != map.end()) continue;
		map[item] = 1;
		if(map.find(item-1) != map.end()){
			longest = max(longest, mergeCluster(map, item-1, item));
		}
		if(map.find(item+1) != map.end()){
			longest = max(longest, mergeCluster(map, item, item+1));
		}
	}
	return longest;	
} 
int main()
{
	vector<int> iv{100, 4, 200, 1, 3, 2};
	cout << Soluciont(iv) << endl;
	return 0;
}
