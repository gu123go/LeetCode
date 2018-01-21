/*
** Author     : Gzh 
** Datetime   : 1/6
** Problom    : Suppose a sorted array is rotated at some pivot unknown to you beforehand.
				(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
				You are given a target value to search. If found in the array return its index, otherwise return -1.
				You may assume no duplicate exists in the array.
*/

#include <iostream>
#include <vector>

using namespace std;

int Solution(const vector<int> &iv, int target)
{
	auto s = iv.begin();
	auto e = iv.end()-1;
	while(s <= e){
		auto mid = s + (e - s) / 2;
		if(*mid == target) return (mid-iv.begin());
		if(*mid >= *s){
			if(*mid > target && target >= *s) e = mid;
			else s = mid + 1;
		}else{
			if(*mid < target && *e >= target) s = mid + 1;
			else e = mid;
		}
	}
	return -1;
}

int main()
{
	vector<int> iv{5,6,7,8,9,0,1,2,3,4};
	for(int i = 0; i < 9; ++i){
		int ret = Solution(iv, i);
		cout << i << "\t" << ret << endl;
	}

	return 0;	
}



