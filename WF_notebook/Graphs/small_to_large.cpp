/* Answer Queries for All vertices in amortized complexity 
   Complexity:  dfs_sz O(n) | dfs O(nlogn)
  Problem: find all pairs (u, v) with d(u, v) <= val
*/
int n, m;
namespace seg{ // Auxiliary DS
	int t[2 * MAXN];
	void modify(int p, int value) {  
		for (t[p+=n]+=value;p>1;p>>=1)t[p>>1]=t[p]+t[p^1];
	}

	int query(int l, int r) { // sum on interval [l, r)
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
			sz[v] += sz[x]; // adj[v][0] is the heavier son
			if (sz[x] > sz[adj[v][0]] or adj[v][0] == p)
				swap(x, adj[v][0]);
		}
	}// in[v]-out[v], time of all decendents of v
	out[v] = clk - 1;
}
ll dfs(int v, int p, int val, bool keep = 0){
	int bc = adj[v].size() > 1 ? adj[v][0] : -1; // heavy son
	ll ans = 0;

	for (int u : adj[v])
		if (u != p and u != bc)
			ans += dfs(u, v, val);

	if (bc != -1)
		ans += dfs(bc, v, val, 1);// save answer for heavy son

	for (auto u : adj[v])
		if (u != p and u != bc){
			for(int x = in[u]; x <= out[u]; x++)
				if (val + (2 * hgt[v]) - hgt[rt[x]] > 0)
					ans += seg::query(0, val + (2 * hgt[v]) - 
						hgt[rt[x]] + 1);
	// compute pairs with other trees
			for (int x = in[u]; x <= out[u]; x++)// sum subtree
				seg::modify(hgt[rt[x]], 1);
		}

	ans += seg::query(0, val + hgt[v] + 1);
	seg::modify(hgt[v], 1); // add v

	if (!keep) // erase work of light son
		for(int x = in[v]; x <= out[v]; x++)
			seg::modify(hgt[rt[x]], -1); 
	return ans;
}
void solve(int r){ // 1 is the root
	memset(seg::t, 0, sizeof seg::t);
	hgt[r] = clk = 0;
	dfs_sz(r);
	ll ans = dfs(r, r, val);
}