/*
** Author 	: Gzh
** Datetime : 1/30
** Problom  : Given a linked list, swap every two adjacent nodes and return its head
				For example, Given 1->2->3->4, you should return the list as 2->1->4->3.
				Your algorithm should use only constant space. You may not modify the values in the list, only nodes
				itself can be changed
*/

#include <iostream>
#include <vector>
#include "list.h"
using namespace std;

template<class T>
using Node = __list_node<T>;

template<class T>
void init(Node<T> *&head, const vector<int> &nums)
{
	if(nums.size() == 0) return ;
	head = new Node<T>(nums[0]);
	Node<T> *pre = head;
	for(int i = 1; i < nums.size(); ++i){
		Node<T> *p = new Node<T>(nums[i]);
		pre->next = p;
		pre = p;
	}
}

template<class T>
Node<T>* Solution(Node<T> *&head)
{
	Node<T> dummy(-1);
	dummy.next = head;
	if(!head || !head->next) return dummy.next;
	Node<T> *pre = &dummy, *cur = head, *next = cur->next;

	while(next){
		cur->next = next->next;
		next->next = pre->next;
		pre->next = next;
		
		pre = cur;
		cur = next;
		next = next->next;
	}
	return dummy.next;

}

int main()
{
	vector<int> iv{1,2,3,4,6};
	Node<int> *head = nullptr;
	init(head, iv); 
	
	Node<int> *p = Solution(head);

	for(; p; p=p->next)
		cout << p->val;


	return 0;
}
