/* 
** Author     : Gzh 
** Datetime	  : 1/6
** Problom    : Follow up for ¡±Remove Duplicates¡±: What if duplicates are allowed at most twice?
				For example, Given sorted array A = [1,1,1,2,2,3],
				Your function should return length = 5, and A is now [1,1,2,2,3]
*/

#include <iostream>
#include <vector>
using namespace std;


int Solution(vector<int> &iv)
{
	
}

int main()
{
	vector<int> iv{1,2,3,4,5};
	int ret = Solution(iv);
	for(int i = 0; i < iv.size(); ++i)
		cout << iv[i] << "\t";
	return 0;	
}

