/*
** Author 	: Gzh
** Datetime : 1/28
** Problom  : Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater
				than or equal to x.
				You should preserve the original relative order of the nodes in each of the two partitions.
				For example, Given 1->4->3->2->5->2 and x = 3, return 1->2->2->4->3->5.
*/

#include <iostream>
#include <vector>
#include "./list.h"

using std::vector;

template<typename T>
__list_node<T>* Solution(__list_node<T> *pListNode, int x, unsigned int size)
{
	__list_node<T> left_dummy;
	__list_node<T> right_dummy;
	__list_node<T> *left_cur = &left_dummy;
	__list_node<T> *right_cur = &right_dummy;

	__list_node<T> *p = pListNode;
	for(int i = 0; i < size; ++i, p=p->next){
		if(p->val >= x){
			 right_cur->next = p;
			 right_cur = p;
		}
		else{
			left_cur->next = p;
			left_cur = p;
		}
	}
	left_cur->next = right_dummy.next;

	return left_dummy.next;
}

//initialize a list
template<class T>
void init(__list_node<T> **pNode, const vector<int> &iv)
{
	__list_node<T> *p, *head = new __list_node<T>;
	head->next = nullptr;
	p = head;
	for(int i = 0; i < iv.size(); ++i){
		__list_node<T> *node = new __list_node<T>;
		node->val = iv[i];
		p->next = node;
		p = node;
	}
	*pNode = head->next;
}

int main()
{

	__list_node<int> *p;

	vector<int> iv{1,4,3,2,5,2};
	init(&p, iv);
	__list_node<int>* res = Solution(p, 3, iv.size());
	p = res;

	for(int i = 0; i < iv.size(); ++i){
		std::cout << p->val;
		p = p->next;
	}

	return 0;
}