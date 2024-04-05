/*
	Title: Centroid decomposition
	Description: Algorithm to do divide and conquer on trees
	Complexity: O(n log n)
	Details: Function called dfs is used to solve the specific problem
*/
int sz[MAXN];
vector<int> adj[MAXN], cents;
void find(int v, int p, int tree_sz){
	sz[v] = 1;
	bool ok = true;
	for(auto x : adj[v]){
		if(x != p) {
			find(x, v, tree_sz);
			sz[v] += sz[x];
			if(sz[x] > tree_sz / 2) ok = false;
		}
	}
	if(ok && tree_sz - sz[v] <= tree_sz / 2) cents.pb(v);
}
int cur[MAXN], tot[MAXN];
void dfs(int v, int p, int h){
	cur[h]++;
	sz[v] = 1;
	for(auto x : adj[v]){
		if(x != p) {
			dfs(x, v, h + 1);
			sz[v] += sz[x];
		}
	}
}
int decompose(int v, int tree_sz){
	cents.clear();
	find(v, -1, tree_sz);
	v = cents[0];
	int ans = 0;
	tot[0]++;
	for(auto x : adj[v]){ 
		// Solve the problem in O(n). It may change a lot from problem to problem 
		dfs(x, v, 1);
		for(int i = 1; i <= sz[x]; i++){
			// do something
		}
		for(int i = 1; i <= sz[x]; i++) 
			tot[i] += cur[i], cur[i] = 0;
	}
	// Reset for the next iteration
	for(int i = 0; i < tree_sz; i++) cur[i] = 0, tot[i] = 0;
	for(auto x : adj[v]){
		for(int i = 0; i < adj[x].size(); i++) // Erase v from adj of x
			if(adj[x][i] == v){
				adj[x].erase(adj[x].begin() + i, adj[x].begin() + i + 1);
				break;
			}
		ans += decompose(x, sz[x]);
		adj[x].pb(v);
	}			
	return ans;
}
