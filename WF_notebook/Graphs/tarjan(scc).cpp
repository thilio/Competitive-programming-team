/*Build the strong connected condensation digraph O(E + V)*/
int n, clk, sn, id;
int pre[MAXN], lo[MAXN], stk[MAXN], scc[MAXN];
vector<int> adj[MAXN], adjscc[MAXN];
void dfs_scc(int v){
	pre[v] = lo[v] = clk++;
	stk[sn++] = v;
	for (auto x : adj[v]){
		if (pre[x] == -1) dfs_scc(x);
		lo[v] = min(lo[v], lo[x]);
	}
	if (lo[v] == pre[v]){
		int u;
		do {
			u = stk[--sn];
			scc[u] = id;
			lo[u] = INF;
		} while (u != v);
		id++;
	}
}
int findscc(){
	fill(pre, pre + n + 1, -1);
	clk = sn = id = 0;
	for (int v = 0; v < n; v++) // 0 indexed
		if (pre[v] == -1)
			dfs_scc(v);
	return id; // number of strong components
}