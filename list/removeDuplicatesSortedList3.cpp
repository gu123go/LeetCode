#include <iostream>
#include <vector>
#include "list.h"

template<class T>
void Solution(list<T> &il)
{
	bool duplicate = false;
	for(auto pre = il.begin(), p = pre+1; p != il.end(); ){
		while(p != il.end() && *pre == *p){
			duplicate = true;
			p = il.erase(p);
		}
		if(duplicate){
			pre = il.erase(pre);
			duplicate = false;
		}
		if(p != il.end()){
			pre = p;
			++p;
		}
	}
}


//Recursive
template<class T>
void Solution1(list<T> &il, typename list<T>::iterator pre, typename list<T>::iterator p)
{
	if(p == il.end()) return;
	if(*pre == *p){
		while(*pre == *p){
			p = il.erase(p);
		}
		pre = il.erase(pre);
	}
	pre = p;
	++p;
	
	Solution1(il, pre, p);
}

int main()
{
	list<int> mylist = list<int>({1,2,3,3,4,4,5,6});

	Solution1(mylist, mylist.begin(), mylist.begin()+1);
	for(auto item : mylist)
		std::cout << item << "\t";

	return 0;
}
