/*
** Author 	: Gzh
** Datetime : 1/24
** Problom  : You are given an n × n 2D matrix representing an image.
				Rotate the image by 90 degrees (clockwise).
				Follow up: Could you do this in-place?
** 时间复杂度O(n^2), 空间复杂度O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Solution1(vector<vector<int>> &nums)
{
	size_t len = nums.size();
	//副对角线翻转
	for(int i = 0; i < len; ++i){
		for(int j = 0; j < len-i; ++j){
			swap(nums[i][j], nums[len-j-1][len-i-1]);
		}
	}
	//水平中线翻转
	for(int i = 0; i < len/2; ++i){
		for(int j = 0; j < len; ++j){
			swap(nums[i][j], nums[len-i-1][j]);
		}
	}
}

void Solution2(vector<vector<int>>& nums)
{
	size_t len = nums.size();

	//水平中线翻转
	for(int i = 0; i < len/2; ++i){
			for(int j = 0; j < len; ++j)
				swap(nums[i][j], nums[len-i-1][j]);
	}
	//主对角线翻转
	for(int i = 0; i < len; ++i){
		for(int j = i+1; j < len; ++j)
			swap(nums[i][j], nums[j][i]);
	}
	
}

int main()
{

	vector<vector<int>> ivs{{1,2,3},{4,5,6},{7,8,9}};
	Solution2(ivs);
	for(auto &items : ivs){
		for(auto item : items){
			cout << item << "\t";
		}
		cout << endl;
	}
	return 0;
}