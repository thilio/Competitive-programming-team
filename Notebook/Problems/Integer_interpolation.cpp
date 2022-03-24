/*
   Title: Polynomial interpolation of integer points
   Description: Use math computations to evaluate the interpolation using only addition and subtraction
   Complexity: O(n*(n + m)), where n is the degree of the polynomial and m is the number of points
   			   you want to evaluate
   Details: The given points (and the ones you want to evaluate) must be equally spaced. The idea
   			is to compute P(x) - P(x - 1), since this result in a polynomial of degree n - 1,
   			until we reach a polynomial of degree 0, a constant, and then reconstruct the table mat.
   			mat[i][j] " = " the polynomial of degree i evaluated at j.
   Solves: https://www.spoj.com/problems/CMPLS/
*/

#include "bits/stdc++.h"
using namespace std;

const int MAXS = 110;
const int MAXC = 110;

long long int mat[MAXS][MAXS + MAXC];

int main(){

	int T;
	cin >> T;
	while(T--){
		int s, c;
		cin >> s >> c;

		for(int j = 1; j <= s; j++){
			cin >> mat[s - 1][j];
		}

		for(int i = s - 2; i >= 0; i--){
			for(int j = s - i; j <= s; j++){
				mat[i][j] = mat[i + 1][j] - mat[i + 1][j - 1];
			}
		}

		long long int val = mat[0][s];

		for(int j = s + 1; j <= s + c; j++){
			mat[0][j] = val;
		}

		for(int j = s + 1; j <= s + c; j++){
			for(int i = 1; i < s; i++){
				mat[i][j] = mat[i - 1][j] + mat[i][j - 1];
			}
		}

		for(int j = s + 1; j <= s + c; j++){
			cout << mat[s - 1][j] << ' ';
		}

		cout << endl;
	}

}
