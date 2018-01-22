/*
** Author 	: Gzh
** Datetime : 1/21
** Problom  : Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules
				http://sudoku.com.au/TheRules.aspx.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool check(char ch, bool used[9])
{
	if(ch == '.') return true;
	if(used[ch-'1']) return false;
	return used[ch-'1'] = true;
}


bool Solution(const vector<vector<char>> &board)
{
	bool used[9];


	for(int i = 0; i < 9; ++i){
		fill(used, used+9, false);
		for(int j = 0; j < 9; ++j)
			if(!check(board[i][j], used))
				return false;

		fill(used, used+9, false);
		for(int j = 0; j < 9; ++j)
			if(!check(board[j][i], used))
				return false;
	}

	fill(used, used+9, false);

	for(int i = 0; i+3 <= 9; i+=3){
		for(int j = 0; j+3 <= 9; j+=3){

			fill(used, used+9, false);
			for(int m = i; m < i+3; ++m){
				for(int n = j; n < j+3; ++n){
					if(!check(board[m][n], used))
						return false;
					//cout << m << "," << n << "\t\t";
					
				}
				cout << endl;
			}
			cout << endl;
		}
	}
}

int main()
{
	vector<vector<char>> cvs;
	Solution(cvs);
	return 0;
}