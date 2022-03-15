/*
   Title: Mo's algorithm with Hilbert Curves
   Description: Mo's algorithm (with other sorting) to solve number of distinct elements in range
   Complexity: O(n sqrt(q))
   Details: Instead of the usual Mo's sorting, we use an order based
   			in Hilbert curves. This can speed up the algorithm in
   			some cases. Use when time limit is tight
   Solves: https://www.spoj.com/problems/DQUERY/
   Credits: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/mo.cpp
*/

#include "bits/stdc++.h"
using namespace std;

const int MAXA = 1000100;

vector<int> v, resp;
int freq[MAXA];

int l = 0, r = -1;
int ans, sq;

inline long long int hilbert(int x, int y) {
	static int N = (1 << 20);
	int rx, ry, s;
	long long int d = 0;
	for (s = N/2; s>0; s /= 2) {
		rx = (x & s) > 0;
		ry = (y & s) > 0;
		d += s * (long long int)(s) * ((3 * rx) ^ ry);
		if (ry == 0) {
			if (rx == 1) {
				x = N-1 - x;
				y = N-1 - y;
			}
			swap(x, y);
		}
	}
	return d;
}

struct qry{
	int l, r, ind;
	long long int h;

	qry() : l(0), r(0), ind(0), h(0) {} 
	qry(int _l, int _r, int _ind): l(_l), r(_r), ind(_ind), h(hilbert(_l, _r)) {}
 
	bool operator < (const qry& x) const{
		return h < x.h;
	}
};


 
void add(int val){
	freq[val]++;
	if(freq[val] == 1) ans++;
}
 
void remove(int val){
	freq[val]--;
	if(freq[val] == 0) ans--;
}
 
int query(int x, int y){
	while(r < y) add(v[++r]);
	while(l > x) add (v[--l]);
	while(r > y) remove(v[r--]);
	while(l < x) remove(v[l++]);
	return ans;
}
 
int main(){

	int n, q;
 
	cin >> n;
	v.resize(n);

	sq = (int)ceil(sqrt(n));

	for(int i = 0; i < n; i++){
		cin >> v[i];
	}

	cin >> q;
	vector<qry> Q;

	resp.resize(q);

	for(int i = 0; i < q; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;

		Q.push_back({a, b, i});
	}

	sort(Q.begin(), Q.end());

	for(auto x: Q){
		resp[x.ind] = query(x.l, x.r);
	}

	for(auto x: resp){
		cout << x << endl;
	}
 
 
 
 
}