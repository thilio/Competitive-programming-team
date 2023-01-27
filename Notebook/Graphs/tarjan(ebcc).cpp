/*
   Title: Tarjan's algorithm for edge-biconnected component (ebcc)
   Description: Build the edge-biconnected condensation graph
   Complexity: O(E + V)
   
   Details: Two vertices u and v are in the same componete if they 
   are connected by two edge disjoint paths.(Notice, may repeat a vertex)

	Bridges separate ebcc and are the edges of the condensed graph.
*/

const int MAXN = 4e5 + 10; // Graph Size

int n, m, sn, clk, id;
int pre[MAXN], lo[MAXN], stk[MAXN], ebcc[MAXN]; // ebcc[v] is the bicconected component of v
vector<int> adj[MAXN], adjbcc[MAXN];

void dfs_ebcc(int v, int p){
	lo[v] = pre[v] = clk++;
	stk[sn++] = v;

	for (auto x : adj[v]){
		if (pre[x] == -1){ 
			dfs_ebcc(x, v); 
			lo[v] = min(lo[v], lo[x]);
		} 
		else if (x != p) 
			lo[v] = min(lo[v], pre[x]); 
	} 
	if (lo[v] == pre[v]){ 
		int u;
		do {
			u = stk[--sn];
			ebcc[u] = id;
		} while (u != v);
		id++;
	}
}

int findebcc(){
	fill(pre, pre + n + 1, -1);
	sn = clk = id = 0;
	for (int v = 0; v < n; v++) // 0 indexed
		if (pre[v] == -1)
			dfs_ebcc(v, v);
		
	return id;
}

void build_ebcc_graph(){ // Build ebcc condensation tree
	for (int v = 0; v < n; v++)
		for (auto x : adj[v])
			if (ebcc[v] != ebcc[x])
				adjbcc[ebcc[v]].push_back(ebcc[x]);
}