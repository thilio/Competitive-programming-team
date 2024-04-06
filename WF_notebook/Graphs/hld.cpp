/*Decomposes a tree into chains
Complexity: build O(V) | query_path - O(log(V)*DS)
	update_path O(log(V)*DS) | query_subtree O(DS)
	update_subtree O(DS) | O(log(V)) | anc O(1)
DS is the compexity of the auxiliary data structure.
HLD works on vertices. Here, things must be associative.
When using HLD for dges, some indexes must be changed. 
Think of an edge as the decendent vertex.*/
#define oper(a, b) a + b // opration 
#define NEUT 0 // neutral element
namespace seg{}; //can be any assocative DS
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
					swap(x, adj[v][0]); //Heavy son in adj[v][0]
			}
		}
	}
	void dfs_build(int v, int p = -1){
		pos[v] = clk++; // subtree of v stored sequentially
		for (auto &x : adj[v])
			if (x != p){
				pai[x] = v;
				if (x == adj[v][0])
					h[x] = h[v]; // in the same chain as parent
				else
					h[x] = x; // new head of the chain
				dfs_build(x, v);
			}
	}
	void build(int r){ // builds HLD with root r
		clk = 0;	h[r] = r;
		dfs_sz(r);
		dfs_build(r);
		// now, prepare the data structure
	}
	
	// Comments are the changes when dealing with edges

	void update_path(int a, int b, int x){
		// if (a == b) return; // Edges, meaningless queries
		if (pos[a] < pos[b])
			swap(a, b);
		if (h[a] == h[b])
			return (void) 
				seg::update(pos[b], pos[a], x);//pos[b] + 1
		seg::update(pos[h[a]], pos[a], x);
		update_path(pai[h[a]], b, x);
	}
	int query_path(int a, int b){
		// if (a == b) return 0; // Edges, meaningless queries
		if (pos[a] < pos[b]) swap(a, b);
		if (h[a] == h[b])
			return seg::query(pos[b], pos[a]); // pos[b] + 1
		return oper(seg::query(pos[h[a]], pos[a]), 
			query_path(pai[h[a]], b));
	}
	void update_subtree(int a, int x){
		// if(sz[a] == 1)return; // Edges, meaningless queries
		seg::update(pos[a], pos[a] + sz[a] - 1, x);//pos[a]+1
	}
	int query_subtree(int a){ // ubtree stored sequentially
		// if (sz[a] == 1) return 0; //meaningless queries
		return seg::query(pos[a], pos[a]+sz[a]-1);//pos[a]+1
	}
	int lca(int a, int b){ // lca of a and b
		if (pos[a] < pos[b]) swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}
	bool anc(int a, int b){ // a is ancestor of b?
		return pos[a] < pos[b] and pos[b] < pos[a] + sz[a];
	}
}
