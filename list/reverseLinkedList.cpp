/*
** Author 	: Gzh
** Datetime : 1/27
** Problom  : Reverse a linked list from position m to n. Do it in-place and in one-pass.
				For example: Given 1->2->3->4->5->nullptr, m = 2 and n = 4,
				return 1->4->3->2->5->nullptr.
				Note: Given m, n satisfy the following condition: 1 ≤ m ≤ n ≤ length of list.
*/

#include <iostream>
#include "./list.h"
using std::cout;
using std::endl;

/*
template<typename T>
void Solution(__list_node<T> *pListNode, int m, int n)
{
	__list_node<T> *p = pListNode;
	int tmp = m;
	--m;
	while(p && --m){
		p = p->next;
	}
	__list_node<T> *pre = p, *q = p->next;
	p = q;
	__list_node<T> *pNext = p->next;
	__list_node<T> *pNNext = pNext->next;
	for(int i = tmp; i < n && pNext; ++i){
		pNext->next = p;
		p = pNext;
		pNext = pNNext;
		pNNext = pNNext->next;
	}
	pre->next = p;
	q->next = pNext;
}
*/

template<typename T>
__list_node<T> *Solution(__list_node<T> *head, int m, int n)
{
	__list_node<T> dummy;
	dummy.val = -1;
	dummy.next = head;
	
	__list_node<T> *prev = &dummy;
	for(int i = 0; i < m-1; ++i)
		prev = prev->next;
	__list_node<T> * const head2 = prev;
	
	prev = head2->next;
	__list_node<T> *cur = prev->next;
	for(int i = m; i < n; ++i){
		prev->next = cur->next;
		cur->next = head2->next;
		head2->next = cur;
		cur = prev->next;        //头插法
	}
	
	return dummy.next;
		
} 

int main()
{
	list<int> mylist = list<int>({1,2,3,4,5});
	__list_node<int> *pListNode = mylist.getNode();

	__list_node<int> *p = Solution(pListNode, 2, 4);
	//p = pListNode;
	for(; !mylist.isEnd(p); p=p->next)
		cout << p->val;
	cout << endl;
	return 0;
}
