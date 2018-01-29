/*
** Author 	: Gzh
** Datetime : 1/29
** Problom  : Given a sorted linked list, delete all duplicates such that each element appear only once.
				For example,
				Given 1->1->2, return 1->2.
				Given 1->1->2->3->3, return 1->2->3.
** Recursive goto removeDuplicatesSortedList2.cpp
*/ 


#include <iostream>
#include <vector>
#include "list.h"

using std::cout;
using std::endl;
using std::vector;

template<class T>
using Node = __list_node<T>;

template<class T>
void init(Node<T>*& p, const vector<int> &nums)
{
	if(nums.size() == 0) return;
	p = new Node<int>(nums[0]);
	auto s = nums.begin();
	auto e = nums.end();
	Node<T> *pre = p, *q;
	while(++s != e){
		q = new Node<T>(*s);
		pre->next = q;
		pre = q;
	}
}

template<class T>
void Solution(Node<T>* p)
{
	Node<T> dummy(p->val+1);
	Node<T> *pre = &dummy;
	while(p){
		if(pre->val == p->val){
			pre->next = p->next;
			delete p;
		}else{
			pre = p;
		}
		p = pre->next;
	}
}

template<class T>
void Solution1(list<T> &mylist)
{
	for(auto pre = mylist.begin(), p = pre+1; p != mylist.end();){
		if(*p == *pre) p = mylist.erase(p);
		else{
			pre = p;
			++p;	
		} 
	}
}

int main()
{

	//Node<int> *pHead, *p;
	//vector<int> iv{1,1,2,3,3};
	//init(pHead, iv);
	//Solution(pHead);
//	for(p = pHead; p; p=p->next){
//		delete p;
//}
	
	list<int> mylist = list<int>({1,1,2,3,3});
	Solution1(mylist);
	
//	for(auto s = mylist.begin(); s != mylist.end(); ++s)
//		cout << *s;
	return 0;
}
