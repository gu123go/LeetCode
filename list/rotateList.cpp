/*
** Author 	: Gzh
** Datetime : 1/30 
** Problom  : Given a list, rotate the list to the right by k places, where k is non-negative.
				For example: Given 1->2->3->4->5->nullptr and k = 2, return 4->5->1->2->3->nullptr.
*/

#include <vector>
#include <iostream>
#include "list.h"

using std::cout;
using std::endl;
using std::vector;

template<class T>
using Node = __list_node<T>;

/*
template<class T>
void display(Node<T> *p)
{
	while(p){
		cout << p->val;
		p=p->next;
	}
}
*/

template<class T>
void init(Node<T>*& head, const vector<int> &nums)
{
	head = new Node<T>(nums[0]);
	Node<T> *p, *pre = head ;
	for(int i = 1; i < nums.size(); ++i){
		p = new Node<T>(nums[i]);
		pre->next = p;
		pre = p; 
	}
}

template<class T>
Node<T>* Solution(Node<T> *head, int k)
{
	Node<T> *p = head, *pre;
	int len = 1;       //note : begin whth 1
	while(p){
		++len;
		pre = p;
		p=p->next;
	}
	cout << pre->val << endl;
	pre->next = head;
	int position = len - k%len;
	p = head;
	while(position--) 
		p = p->next;
	head = p->next;
	p->next = nullptr;
	return head;
}

int main()
{

	Node<int> *p;
	vector<int> iv{1,2,3,4,5};
	init(p, iv);
	
	p = Solution(p, 2);
	
	for(auto q = p; q; q = q->next)
		cout << q->val;
	return 0;
}
