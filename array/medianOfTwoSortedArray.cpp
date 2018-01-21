/*
** Author   : Gzh
** Datetime : 1/6
** Problom  : There are two sorted arrays A and B of size m and n respectively. Find the median of the two sorted
			  arrays. The overall run time complexity should be O(log(m + n)).
*/

#include <iostream>
#include <vector>
using namespace std;

int find_kth(vector<int>::const_iterator A, int m, vector<int>::const_iterator B, int n, int k)
{
	if(m > n) find_kth(B, n, A, m, k);
	if(m == 0) *(B+k-1);
	if(k == 1) return min(*A, *B);
	
	int ia = min(k/2, m), ib = k - ia;
	if(*(A+ia-1) < *(B+ib-1))
		return find_kth(A+ia, m-ia, B, n, k-ia);
	if(*(A+ia-1) > *(B+ib-1))
		return find_kth(A, m, B+ib, n-ib, k-ib);
	else return A[ia-1];
}

int Solution(const vector<int> &A, const vector<int> &B)
{
	int total = A.size() + B.size();
	if(total & 0x01){
		return find_kth(A.begin(), A.size(), B.begin(), B.size(), total/2+1);
	}else{
		cout << "odd\n";
		//return find_kth(A.begin(), A.size(), B.begin(), B.size(), total/2);
		return (find_kth(A.begin(), A.size(), B.begin(), B.size(), total/2) + 
			find_kth(A.begin(), A.size(), B.begin(), B.size(), total/2+1)) / 2.0;
	}
}

int main()
{
	vector<int> iv1{1,2,3,4,5,6};
	vector<int> iv2{7,8, 9, 10};
	cout << Solution(iv1, iv2);
	return 0;
}
