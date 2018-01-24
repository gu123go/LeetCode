/*
** Author 	: Gzh
** Datetime : 1/24
** Problom  : Given a number represented as an array of digits, plus one to the number.
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Solution(vector<int> &digits, int digit)
{
	int k = digit;

	//for_each(digits.rbegin(), digits.rend(), [&k](int &d){d += k; k = d/10; d %= 10;});

	for(int i = digits.size()-1; i >= 0; --i){
		int c = digits[i] + k;
		digits[i] = c % 10;
		k = c / 10;
	}
	if(k > 0)
		digits.insert(digits.begin(), 1);.
	0
}

int main()
{
	vector<int> digits{1,2,3,4,5,6,7,8,9};
	Solution(digits, 8);
	for(auto item : digits)
		cout << item;
	cout << endl;

	return 0;
}