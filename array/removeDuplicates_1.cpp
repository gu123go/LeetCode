/**
** Author    : Gzh
** Datetime  : 1/5
** Problom   : Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
			   Do not allocate extra space for another array, you must do this in place with constant memory.
			   For example, Given input array A = [1,1,2],
			   Your function should return length = 2, and A is now [1,2]
*/

#include <iostream>
#include <vector>
#include <algorithm>

template<typename InIt, typename OutIt>
OutIt removeDuplicates(InIt first, InIt last, OutIt output)
{
	while(first != last){
		*output++ = *first;
		first = upper_bound(first, last, *first); 
	}
}

template<typename T>
int Solution(std::vector<T> &param)
{
	//return std::distance(param.begin(), std::unique(param.begin(), param.end()));
	//return std::distance(param.begin(), removeDuplicates(param.begin(), param.end(), param.begin()));
	if(param.size() < 2) return param.size();
	auto itr = param.begin(), index = param.begin();
	while(itr != param.end()) {
		if(*itr != *index){
			*++index = *itr;
		}
		++itr;
	}
	return index-param.begin();
}


int main()
{
	std::vector<int> iv{1,2, 3, 4, 5, 5};
	int ret = Solution(iv);
	std::cout << ret << std::endl;
	for(auto itr = iv.begin(); itr != iv.end(); ++itr)
		std::cout << *itr << "\t";
	
	return 0;	
}
