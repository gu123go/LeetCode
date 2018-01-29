#include <iostream>
#include "list.h"

void Solution(list<int> &il, list<int>::iterator pre, list<int>::iterator p)
{
	if(il.end() == p) return;
	if(*pre == *p){
		p = il.erase(p);
	}else{
		pre = p;
		++p;
	}
	Solution(il, pre, p);
}

int main()
{
	list<int> mylist = list<int>({1,1,2,6,7,7,7,8});
	Solution(mylist, mylist.begin(), mylist.begin()+1);
	for(auto itr = mylist.begin(); itr != mylist.end(); ++itr)
		std::cout << *itr;
	return 0;
}
