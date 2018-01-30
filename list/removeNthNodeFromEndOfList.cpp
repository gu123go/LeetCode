/*
** Author 	: Gzh
** Datetime : 1/30
** Problom  : Given a linked list, remove the nth node from the end of list and return its head.
				For example, Given linked list: 1->2->3->4->5, and n = 2.
				After removing the second node from the end, the linked list becomes 1->2->3->5.
				Note:
				• Given n will always be valid.
				• Try to do this in one pass.
*/

#include <iostream>
#include <vector>
#include "list.h"
using std::vector;
using std::cout;
using std::endl;

template<class T>
void Solution(list<T> &il, int n)
{
	auto p = il.begin();
	while(n--) ++p;
	auto q = il.begin();
	while(p != il.end()){
		++p;
		++q;
	}
	il.erase(q);
}

int main()
{
	list<int> mylist = list<int>({1,2,3,4,5});
	Solution(mylist, 2);
	for(auto item : mylist)
		cout << item;
	return 0;
}