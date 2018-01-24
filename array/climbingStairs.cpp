/*
** Author 	: Gzh
** Datetime : 1/24
** Problom  : You are climbing a stair case. It takes n steps to reach to the top.
				Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int Solution1(int n)
{
	int a = 0, b = 1;
	for(int i = 0; i < n; ++i){
		int tmp = a;
		a += b;
		b = tmp;
	}
	return a;
}

//通项公式
int Solution2(int n)
{
	const double s = sqrt(5);
	return ceil(1/s*(pow((1+s)/2, n) - pow((1-s)/2, n)));
}

int main()
{
	cout << Solution1(12) << endl;
	cout << Solution2(12) << endl;
	return 0;
}