/*
   Title: Sack, Small to Large
   Description: Answer Tree Queries for All in amortized complexity 
   Complexity:  dfs_sz O(n)
		dfs O(nlogn)

   Details: Computes all queries by saving the answer of the havier son. 

   In this problem we will find all pairs (u, v) with d(u, v) <= val
*/

typedef long long int ll;
const int MAXN = 5e5 + 10;

int n, m;

namespace seg{ // Auxiliary DS
	int t[2 * MAXN];

	void modify(int p, int value) {  
		for (t[p += n] += value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
	}

	int query(int l, int r) {  // sum on interval [l, r)
		int res = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) res += t[l++];
			if (r&1) res += t[--r];
		}
		return res;
	}
}

int sz[MAXN], hgt[MAXN], in[MAXN], out[MAXN], rt[MAXN], clk;
vector<int> adj[MAXN]; // Adj of the tree

void dfs_sz(int v, int p = -1){
	sz[v] = 1;
	in[v] = clk;
	rt[clk++] = v;
	for (auto &x : adj[v]){
		if (x != p){
			hgt[x] = hgt[v] + 1;
			dfs_sz(x, v);
			sz[v] += sz[x];
			if (sz[x] > sz[adj[v][0]] or adj[v][0] == p) // adj[v][0] is the heavier son
				swap(x, adj[v][0]);
		}
	}
	out[v] = clk - 1; // in[v] - out[v], time of all decendents of v
}

ll dfs(int v, int p, int val, bool keep = 0){
	int bc = adj[v].size() > 1 ? adj[v][0] : -1; // heavy son
	ll ans = 0;

	for (int u : adj[v])
		if (u != p and u != bc)
			ans += dfs(u, v, val);

	if (bc != -1)
		ans += dfs(bc, v, val, 1); // save answer for heavier son

	for (auto u : adj[v])
		if (u != p and u != bc){
			for(int x = in[u]; x <= out[u]; x++)
				if (val + (2 * hgt[v]) - hgt[rt[x]] > 0) // compute pairs with other trees
					ans += seg::query(0, val + (2 * hgt[v]) - hgt[rt[x]] + 1);

		for (int x = in[u]; x <= out[u]; x++) // sum subtree
			seg::modify(hgt[rt[x]], 1);
		}

	ans += seg::query(0, val + hgt[v] + 1);
	seg::modify(hgt[v], 1); // add v

	if (!keep) // erase work of light son
		for(int x = in[v]; x <= out[v]; x++)
			seg::modify(hgt[rt[x]], -1); 
	return ans;
}

void solve(){
	memset(seg::t, 0, sizeof seg::t);
	int root = 1;
	hgt[root] = clk = 0;
	dfs_sz(root);
	ll ans = dfs(root, root, val);
}
