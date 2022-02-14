/*
   Title: Heavy-Light Decomposition Algorithm
   Description: Decomposes a tree into chains
   Complexity:  build O(V);
   		query_path - O(log(V)*DS)
		update_path - O(log(V)*DS)
		query_subtree - O(1*DS)
		update_subtree - O(1*DS)
		lca - O(log(V))
		anc - O(1)

   Details: On the complexity section, DS is the compexity of the auxiliary data structure.
	Here, things must be associative.

	When dealing with HLD for edges, some indexes must be changed. Think of the edge
	as the decendent vertex and store the values in it. HLD works on vertices.
   
   Credits: https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Grafos/LCA-HLD
*/

const int MAXN = 4e5 + 10;

namespace seg{}; // seg is just a model, can be any assocative DS

int n;
vector<int> adj[MAXN];

namespace hld{
	int pos[MAXN], sz[MAXN], pai[MAXN], h[MAXN], clk;

	void dfs_sz(int v, int p = -1){
		sz[v] = 1;
		for (auto &x : adj[v]){
			if (x != p){
				dfs_sz(x, v);
				sz[v] += sz[x];
				if (sz[x] > sz[adj[v][0]] or adj[v][0] == p) 
					swap(x, adj[v][0]); // Heavier son in adj[v][0]
			}
		}
	}

	void dfs_build(int v, int p = -1){
		pos[v] = clk++; // contains the subtree of v sequentially
		for (auto &x : adj[v])
			if (x != p){
				pai[x] = v;
				if (x == adj[v][0])
					h[x] = h[v]; // in the sam echain as the father
				else
					h[x] = x; // new head of the chain
				dfs_build(x, v);
			}
	}

	void build(int r){ // builds HLD with root r
		clk = 0;
		h[r] = r;
		dfs_sz(r);
		dfs_build(r);
		// now, prepare the data structure
	}

	// The indices comments are the ones to change when dealing with edges

	void update_path(int a, int b, int x){
		if (pos[a] < pos[b])
			swap(a, b);
		if (h[a] == h[b])
			return (void) seg::update(pos[b], pos[a], x); // pos[b] + 1
		seg::update(pos[h[a]], pos[a], x);
		update_path(pai[h[a]], b, x);
	}

	int combine(int a, int b){
		// combine query values
	}

	int query_path(int a, int b){
		if (pos[a] < pos[b])
			swap(a, b);
		if (h[a] == h[b])
			return seg::query(pos[b], pos[a]); // pos[b] + 1
		return combine(seg::query(pos[h[a]], pos[a]) , query_path(pai[h[a]], b));
	}

	void update_subtree(int a, int x){
		seg::update(pos[a], pos[a] + sz[a] - 1, x); // pos[a] + 1
	}
	
	int query_subtree(int a){ // subtree is stored sequentially
		return seg::query(pos[a], pos[a] + sz[a] - 1); //pos[a] +1
	}

	int lca(int a, int b){ // lca of a and b
		if (pos[a] < pos[b])
			swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}

	bool anc(int a, int b){ // a is ancestor of b?
		return pos[a] < pos[b] and pos[b] < pos[a] + sz[a];
	}
}
