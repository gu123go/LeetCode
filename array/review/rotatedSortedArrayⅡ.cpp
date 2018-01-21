#include <iostream>
#include <vector>

using namespace std;

int searchInRotatedSortedArray(int target, const vector<int> &iv)
{
	int s = 0, e = iv.size()-1;
	while(s <= e){
		int mid = (s+e)/2;
		if(iv[mid] == target) return mid;
		if(iv[s] < iv[mid]){
			if(iv[s] <= target && iv[mid] > target) e = mid;
			else s = mid+1;
		}
		else if(iv[s] > iv[mid]){
			if(iv[mid] < target && iv[e] >= target) s = mid+1;
			else e = mid;
		}else{
			++s;
		}
		
	}
	return -1;
}

int main()
{
	vector<int> iv{6,6,6,7,7,7,8,9,0,1,2,3,4,5};
	for(int i = 0; i < iv.size()-; ++i){
		cout << searchInRotatedSortedArray(i, iv) << endl;
	} 
} 
