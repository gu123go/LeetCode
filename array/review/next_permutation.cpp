#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename _BidiIt>
bool next_permutation(_BidiIt __first, _BidiIt __last)
{
	if(__first == __last) return false;
	_BidiIt __i = __last;
	if(__first == --__i) return false;

	for(; ;){
		_BidiIt __ii = __i;
		--__i;
		if(__ii != __first && *__i < *__ii){
			_BidiIt __j = __last;
			while(*__i >= *--__j){}
			swap(*__j, *__i);
			reverse(__ii, __last);
			return true;
		}
		if(__ii == __first){
			reverse(__first, __last);
			return false;
		}
	}

}

int main()
{
	vector<int> iv{1,2,3,4};
	do{
		for(auto item : iv)
			cout << item;
		cout << endl;
	}while(::next_permutation(iv.begin(), iv.end()));
	
	return 0;
}
