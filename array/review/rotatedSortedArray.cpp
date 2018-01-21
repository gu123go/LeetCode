#include <iostream>
#include <vector>
using namespace std;


int searchInRotatedSortedArray(int target, const vector<int> &iv)
{
	int s = 0, e = iv.size()-1;
	while(s <= e){
		int mid = (s+e)/2;
		if(iv[mid] == target) return mid;
		if(iv[s] <= iv[mid]){
			if(iv[mid] > target && iv[s] <= target) e = mid;
			else s = mid+1;
		}
		else{
			if(iv[mid] < target && iv[e] >= target) s = mid+1;
			else e = mid;
		}
	}
	return -1;
	
}

int main()
{
	vector<int> iv{5,6,7,8,9,0,1,2,3,4};
	
	for(int i = 0; i < iv.size(); ++i){
		int ret = searchInRotatedSortedArray(i, iv);
		cout << ret << endl;
	}
		
	return 0;
} 
