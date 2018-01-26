/*
** Author 	: Gzh
** Datetime : 1/25
** Problom  : You are given two linked lists representing two non-negative numbers. The digits are stored in reverse
				order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
				Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
				Output: 7 -> 0 -> 8
*/

#include <iostream>
#include <vector>
#include "./list.h"

auto Solution(const list<int> &l1, const list<int> &l2)
	-> list<int>
{
	list<int> result;
	auto s1 = l1.begin(), s2 = l2.begin();
	int d = 0, a, b;
	while(s1 != l1.end() || s2 != l2.end()){
		
		if(s1 == l1.end()){
			a = 0;
		}else{
			a = *s1;
			++s1;
		}
		if(s2 == l2.end()){
			b = 0;
		}else{
			b = *s2;
			++s2;
		}
		int c = a+b+d;
		d = c/10;
		c %= 10;
		
		result.push_back(c);
	}
	return result;
	
}

int main()
{

	list<int> l1 = list<int> ({2, 4, 3});
	list<int> l2 = list<int> ({5, 6, 4});

	list<int> res = Solution(l1, l2);
	for(auto item : res)
		std::cout << item;
	std::cout << std::endl;
	return 0;
}
