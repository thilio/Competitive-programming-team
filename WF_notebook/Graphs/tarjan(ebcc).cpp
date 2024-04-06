/*Build the ebcc graph and finds cut vertices O(E + V)*/
int n, m, sn, clk, id;
int pre[MAXN], lo[MAXN], stk[MAXN], ebcc[MAXN], art[MAXN]; 
vector<int> adj[MAXN], adjbcc[MAXN];

void dfs_ebcc(int v, int p){
	lo[v] = pre[v] = clk++;
	stk[sn++] = v;
	int chd = 0, any = 0;
	for (auto x : adj[v]){
		if (pre[x] == -1){
			chd++;
			dfs_ebcc(x, v); 
			lo[v] = min(lo[v], lo[x]);
			if (lo[x] >= pre[v]) any = true;
		} 
		else if (x != p) lo[v] = min(lo[v], pre[x]); 
	} 

	if (v == p and chd >= 2) art[v] = true;
	if (v != p and any) art[v] = true;

	if (lo[v] == pre[v]){ 
		int u;
		do {
			u = stk[--sn];
			ebcc[u] = id;
		} while (u != v);
		id++;
	}
}
int find_ebcc(){
	fill(pre, pre + n + 1, -1);
	fill(art, art + n + 1, 0);
	sn = clk = id = 0;
	for (int v = 1; v <= n; v++) // 0 indexed
		if (pre[v] == -1)
			dfs_ebcc(v, v);
		
	return id;
}