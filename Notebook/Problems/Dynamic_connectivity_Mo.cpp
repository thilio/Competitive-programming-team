/*
   Title: Mo's algorithm
   Description: Mo's algorithm to solve dynamic connectivity
   Complexity: O(q sqrt(m) log(n))
   Details: DSU with rollback and MO to solve dynamic connectivity
   			querie
   Solves: https://www.codechef.com/problems/GERALD07
*/

#include "bits/stdc++.h"
using namespace std;

const int MAXN = 200200;

int sq;

struct qry{
	int l, r, ind;

	qry() : l(0), r(0), ind(0) {} 
	qry(int _l, int _r, int _ind): l(_l), r(_r), ind(_ind) {}
 
	bool operator < (const qry& x) const{
		if (l/sq == x.l/sq) return (r < x.r);
		return l < x.l;
	}
};

int id[MAXN], sz[MAXN], comp;
stack<array<int, 2>> P;
vector<array<int, 2>> edge;
vector<qry> small, large;
vector<int> resp;


void init(int n){
	for(int i = 1; i <= n; i++){
		id[i] = i;
		sz[i] = 1;
	}
	comp = n;
	while(!P.empty()) P.pop();
}

void reset(int n, int m, int q){
	small.clear();
	large.clear();
	edge.clear();
	init(n);
	resp.resize(q);
	sq = (int)ceil(sqrt(m));
}

int find(int i){
	if(i == id[i]) return i;
	return find(id[i]);
}

bool merge(int u, int v){
	u = find(u);
	v = find(v);
	if(u == v) return false;
	if(sz[u] < sz[v]) swap(u, v);
	id[v] = u;
	sz[u] += sz[v];
	P.push({v, u});
	comp--;
	return true;
}

void unmerge(){
	array<int, 2> a = P.top();
	P.pop();

	id[a[0]] = a[0];
	sz[a[1]] -= sz[a[0]];
	comp++;
}

void solve_small(qry q){
	for(int i = q.l; i <= q.r; i++){
		merge(edge[i][0], edge[i][1]);
	}
	resp[q.ind] = comp;
	while(!P.empty()) unmerge();
}

void solve_large(qry q, int &r){
	while(r <= q.r){
		merge(edge[r][0], edge[r][1]);
		r++;
	}

	int l = (q.l/sq + 1)*sq;
	int ct = 0;

	while(l > q.l){
		l--;
		ct += merge(edge[l][0], edge[l][1]);
	}

	resp[q.ind] = comp;

	while(ct--)
		unmerge(); 
}

int main(){
	
	int T;
	cin >> T;

	while(T--){
		int n, m, q;
		cin >> n >> m >> q;

		reset(n, m, q);

		for(int i = 0; i < m; i++){
			int u, v;
			cin >> u >> v;
			edge.push_back({u, v});
		}

		for(int i = 0; i < q; i++){
			int l, r;
			cin >> l >> r;
			l--; r--;
			if(l/sq == r/sq)
				small.push_back({l, r, i});
			else
				large.push_back({l, r, i});
		}

		for(auto x: small){
			solve_small(x);
		}

		sort(large.begin(), large.end());

		int b = -1;
		int r = 0;
		for(auto x: large){
			if(x.l/sq != b){
				init(n);
				r = ((x.l/sq) + 1)*sq;
				b = x.l/sq;
			}

			solve_large(x, r);
		}

		for(auto x: resp){
			cout << x << endl;
		}

	}
}
