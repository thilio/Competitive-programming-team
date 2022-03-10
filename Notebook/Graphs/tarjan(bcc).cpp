/*
   Title: Tarjan-Hopcroft algorithm for biconnected components
   Description: Finds the block cut tree of a graph
   Complexity:  find_bcc O(E + V)
  
   Details: Builds the block cut decomposition of the tree.
   The tree has at most 2n vertices.

   The function retuns the number of blocks.Be caferul with the tree structure.

   Credits: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/blockCutTree.cpp
*/

vector<int> adj[MAXN];
stack<int> stk;
int clk, pre[MAXN], art[MAXN], pos[MAXN]; // art[v] = 1 if v is a articulation point
vector<vector<int>> blocks, tree;

int dfs_bcc(int v, int p = -1){
	int lo = pre[v] = clk++;
	stk.push(v);
	for (int u : adj[v]) 
		if (u != p) {
			if (pre[u] == -1){
				int val = dfs_bcc(u, v);
				lo = min(lo, val);

				if (val >= pre[v]) {
					art[v]++;
					blocks.emplace_back(1, v);
					while (blocks.back().back() != u){
						blocks.back().push_back(stk.top()); 
						stk.pop();
					}
				}
			// if (val > pre[v]) then edge v-u is a bridge
		}
		else lo = min(lo, pre[u]);
	}
	if (p == -1 and art[v]) 
		art[v]--;
	return lo;
}

int find_bcc(int n){ // retuns the number of 2-connected-components
	for (int i = 0; i < n; i++){ 
		pre[i] = -1; 
		art[i] = 0;
	}

	blocks.clear(), tree.clear();
	while (!stk.empty()) 
		stk.pop();
	
	clk = 0;
	for (int i = 0; i < n; i++) 
		if (pre[i] == -1) 
			dfs_bcc(i);

	tree.resize(blocks.size());
	for (int i = 0; i < n; i++) 
		if (art[i]){
			pos[i] = tree.size(); 
			tree.emplace_back();
		}

	for (int i = 0; i < blocks.size(); i++) 
		for (int v : blocks[i]){
			if (!art[v]) 
				pos[v] = i; // vertex v is in this block
			else{
				tree[i].push_back(pos[v]); // This articulation point connects these vertices
				tree[pos[v]].push_back(i);
			}
	}

	return blocks.size();
}