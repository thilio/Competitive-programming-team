/*
   Title: Square root decomposition
   Description: Use square root decomposition to solve problem in trees
   Complexity: O(q sqrt(n) log(n))
   Details: This problem have two types of queries. Type 1 is paint a node
   			red, initially only node 1 is painted, and type 2, which is the shortest
   			distance to a red node. We can use a square root idea. We store the
   			updates to be done, and when we have sufficiently enough updates
   			we push them all at once.
   Solves: https://codeforces.com/contest/342/problem/E
*/

#include "bits/stdc++.h"
using namespace std;

const int MAXN = 100001;
const int LOGN = 20;
const int INF = 1e9;

int memo[MAXN][LOGN];
int h[MAXN];
int d[MAXN];
int sq;

int n, q;

vector<int> adj[MAXN];

vector<int> red, temp;

void dfs(int v, int p = -1){
	if(p == -1){
		h[v] = 0;
		memo[v][0] = 1;
	}
	else memo[v][0] = p;

	for(int i = 1; i < LOGN; i++){
		memo[v][i] = memo[memo[v][i - 1]][i - 1];
	}
	for(auto x: adj[v]){
		if(x != p){
			h[x] = h[v] + 1;
			dfs(x, v);
		}
	}
}

int lca(int a, int b){
	if(h[a] < h[b]) swap(a, b);

	for(int i = LOGN - 1; i >= 0; i--){
		if(h[memo[a][i]] >= h[b])
			a = memo[a][i];
	}

	if(a == b) return a;

	for(int i = LOGN - 1; i >= 0; i--){
		if(memo[a][i] != memo[b][i]){
			a = memo[a][i];
			b = memo[b][i];
		}
	}

	return memo[a][0];
}

int dist(int a, int b){
	return h[a] + h[b] - 2*h[lca(a, b)];
}

void bfs(){
	for(int i = 1; i <= n; i++)
		d[i] = INF;

	queue<int> q;
	for(auto x: red){
		q.push(x);
		d[x] = 0;
	}

	while(!q.empty()){
		int u = q.front();
		q.pop();

		for(auto x: adj[u]){
			if(d[x] > n){
				d[x] = d[u] + 1;
				q.push(x);
			}
		}
	}
}

void push(){
	for(auto x: temp)
		red.push_back(x);
	temp.clear();
	bfs();
}


int main(){

	cin >> n >> q;

	for(int i = 1; i <= n; i++){
		d[i] = INF;
	}

	sq = (int)ceil(sqrt(n));

	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	temp.push_back(1);

	dfs(1);

	for(int i = 0; i < q; i++){
		int op, v;
		cin >> op >> v;

		if(op == 1){
			temp.push_back(v);
			if(temp.size() >= sq)
				push();
		}
		if(op == 2){
			int mn = d[v];
			for(auto x: temp){
				mn = min(mn, dist(x, v));
			}
			cout << mn << endl;
		}
	}

}
