#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int Solution(vector<int> &ratings)
{
	int n = ratings.size();
	vector<int> iv(n, 0);
	for(int i = 1, inc = 1; i < n; ++i){
		if(ratings[i] > ratings[i-1])
			iv[i] = inc++;
		else
			inc = 1;
	}
	for(int i = n-2, inc = 1; i >= 0; --i){
		if(ratings[i] > ratings[i+1])
			iv[i] = max(iv[i], inc++);
		else
			inc=1;
	}

	return accumulate(iv.begin(), iv.end(), n);
}

int main()
{
	vector<int> iv{4,7,9,0,1,2,3};
	cout << Solution(iv) << endl;
	return 0;
}