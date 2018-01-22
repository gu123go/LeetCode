/*
** Author 	: Gzh
** Datetime : 1/21
** Problom  : 全排列(STL源码)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename _BidirectionalIterator>
inline bool 
	next_permutation(_BidirectionalIterator __first, _BidirectionalIterator __last)
{
	return ::__next_permutation(__first, __last, __gnu_cxx::__ops::__iter_less_iter());
}


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
		if(__i == __last){
			rever(__first, __last);
			return false;
		}
	}
}


int main()
{

	vector<int> iv{1,2,3,4,5};
	vector<char> cv{'a','b','c','d'};
	do{
		for(auto item : cv)
			cout << item;
		cout << endl;
	}while(::next_permutation(cv.begin(), cv.end()));

	return 0;
}