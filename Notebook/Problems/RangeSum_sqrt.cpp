#include "bits/stdc++.h"
using namespace std;

const int MAXN = 100000;
const int SQ = 500;

long long int v[MAXN];
long long int buc[SQ];

int sq;

int id(int i){
	return i/sq;
}

int main(){

	int n, q;

	cin >> n >> q;

	sq = (int)ceil(sqrt(n));

	for(int i = 0; i < n; i++){
		cin >> v[i];
		buc[id(i)] += v[i];
	}

	for(int i = 0; i < q; i++){
		int op;
		cin >> op;

		if(op == 1){
			int j, val;
			cin >> j >> val;

			buc[id(j)] += val - v[j];
			v[j] = val;
		}

		if(op == 2){
			int l, r;
			cin >> l >> r;
			long long int sum = 0;
			int i;

			for(i = l; i < r && id(i) == id(l); i++) sum += v[i];
			for(; i < r && id(i) < id(r); i += sq) sum += buc[id(i)];
			for(; i < r; i++) sum += v[i];

			cout << sum << endl;
		}
	}

}
