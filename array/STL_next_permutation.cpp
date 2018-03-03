/*
** Author 	: Gzh
** Datetime : 1/21
** Problom  : 全排列(STL源码)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace tt{
	
	template<typename _BidirectionalIterator, typename _Compare>
	bool __next_permutation(_BidirectionalIterator __first, _BidirectionalIterator __last, _Compare __comp)
	{
		if(__first == __last) return false;
		_BidirectionalIterator __i = __first;
		++__i;
		if(__i == __last) return false;
	
		__i = __last;
		--__i;
	
		for(; ;){
			_BidirectionalIterator __ii = __i;
			--__i;
			if(__comp(__i, __ii)){
				_BidirectionalIterator __j = __last;
				while(!__comp(__i, --__j)){}
				iter_swap(__i, __j);
				reverse(__ii, __last);
	
				return true;
			}
			if(__i == __first){
				std::reverse(__first, __last);
				return false;
			}
		}
	}
	
	template<typename _BidirectionalIterator>
	inline bool 
		next_permutation(_BidirectionalIterator __first, _BidirectionalIterator __last)
	{
		return tt::__next_permutation(__first, __last, __gnu_cxx::__ops::__iter_less_iter());
	}
	
}


int main()
{

	vector<int> iv{1,2,3,4};
	vector<char> cv{'a','b','c','d'};
	do{
		for(auto item : iv)
			cout << item;
		cout << endl;
	}while(tt::next_permutation(iv.begin(), iv.end()));

	return 0;
}
