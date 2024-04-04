/*
   Title: Tarjan's algorithm for strong connected components (scc)
   Description: Build the strong connected condensation graph
   Complexity:  O(E + V)
   
   Details: Vertices u and v are in the same component if u -> v and v -> u

*/

const int MAXN = 1e5 + 10; // number of vertices

int n, clk, sn, id;
int pre[MAXN], lo[MAXN], stk[MAXN], scc[MAXN]; // scc[v] is the strong component of v
vector<int> adj[MAXN], adjscc[MAXN];

void dfs_scc(int v){
	pre[v] = lo[v] = clk++;
	stk[sn++] = v;
	for (auto x : adj[v]){
		if (pre[x] == -1)
			dfs_scc(x);
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

void build_scc_graph(){ // Build condensation dag
	for (int v = 0; v < n; v++)
		for (auto x : adj[v])
			if (scc[v] != scc[x])
				adjscc[scc[v]].push_back(scc[x]);
}