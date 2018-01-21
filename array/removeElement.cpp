/*
** Author 	: Gzh
** DateTime :1/20
** Problom  : Given an array and a value, remove all instances of that value in place and return the new length.
			  The order of elements can be changed. It doesn’t matter what you leave beyond the new length.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
int Solution(vector<int> &nums, const int target)
{
	size_t i, j;
	for(i = 0, j = 0; j < nums.size(); ++i, ++j){
		while(nums[j] == target) ++j;
		nums[i] = nums[j];
	}
	return i;
}
*/
/*
int Solution(vector<int> &nums, const int target)
{
	size_t index = 0;
	for(size_t i = 0; i < nums.size(); ++i){
		if(nums[i] != target) nums[index++] = nums[i];
	}
	return index;
}
*/

int Solution(vector<int> &nums, int target)
{
	return distance(nums.begin(), remove(nums.begin(), nums.end(), target));
}
int main()
{
	std::vector<int> iv{1,1,12,1,1,1,3,4,7,1,2,8,5,3};
	int ret = Solution(iv, 1);
	for(int i = 0; i < ret; ++i)
		cout << iv[i] << "\t";

	return 0;
}