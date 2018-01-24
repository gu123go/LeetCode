/*
** Author 	: Gzh
** Datetime : 1/24
** Problom  : Given a m × n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
				Follow up: Did you use extra space?
				A straight forward solution using O(mn) space is probably a bad idea.
				A simple improvement uses O(m + n) space, but still not the best solution.
				Could you devise a constant space solution?
** 时间复杂度O(m*n), 空间复杂度O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Solution(vector<int> &nums)
{
	bool first_column_zeros = false, first_row_zeros = false;         //第一行和第一列是否有0
	for(int i = 0; i < nums[0].size(); ++i)
		if(nums[0][i] == 0) first_row_zeros = true;
	for(int i = 0; i < nums.size(); ++i)
		if(nums[i][0] == 0) first_column_zeros = true;


	for(int i = 1; i < nums.size(); ++i){
		for(int j = 1; j < nums[0].size(); ++j)
			if(nums[i][j] == 0){
				nums[0][i] = 0;
				nums[j][0] = 0;
			}
	}
	for(int i = 0; i < nums.size(); ++i){
		for(int j = 0; j < nums[0].size(); ++j)
			if(nums[i][0] == 0 || nums[0][j] == 0){
				nums[i][j] = 0;
		}
	}
	
	if(first_column_zeros){
		for(int i = 0; i < nums[0].size(); ++i)
			nums[i][0] = 0;
	}
	if(first_row_zeros){
		for(int i = 0; i < nums.size(); ++i)
			nums[0][i] = 0;
	}
}

int main()
{
	return 0;
}