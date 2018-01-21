/*
** Author 	: Gzh
** DateTime : 1/20
** Problom  : 全排列(非递归). 
			  see more,please go to http://blog.csdn.net/morewindows/article/details/7370155
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


template<typename BidiIt>
bool get_next_permutation(BidiIt first, BidiIt last)
{
	const auto rfirst = reverse_iterator<BidiIt>(last);
	const auto rlast = reverse_iterator<BidiIt>(first);

	auto pivot = next(rfirst);
	while(pivot != rlast && *pivot >= *prev(pivot)){
		++pivot;
	}

	if(pivot == rlast){
		reverse(rfirst, rlast);
		return false;
	}

	auto change = find_if(rfirst, pivot, bind1st(less<int>(), *pivot));

	swap(*change, *pivot);
	reverse(rfirst, pivot);

	return true;
}

void Solution(vector<int> &nums)
{
	do{
		for(auto item : nums)
			cout << item;
		cout << endl;
	}while(get_next_permutation(nums.begin(), nums.end()));

}

int main()
{
	std::vector<int> vec{1,1,1};
	// get_next_permutation(vec.begin(), vec.end());
	// for(auto item : vec){
	// 	cout << item;
	// }
	// cout << endl;
	Solution(vec);
	return 0;
}
