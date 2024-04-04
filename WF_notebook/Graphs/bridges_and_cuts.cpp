/*
   Title: Tarjan's algorithm for bridges and articulation points
   Description: Find all bridges and articulation points of a graph
   Complexity:  findbc O(E + V + Elog(E))

   Details: One may avoid this log factor using 2-edge-connected compoenents.

   A bridge is a edge such that does not belong to a cycle.
   A articulation point ins a vertex which the removal disconnects the component.
*/

const int MAXN = 1e5 + 10;

int clk, n, m;
int pre[MAXN], lo[MAXN], cut[MAXN]; // cut[v] = 1 is v is an articulation point
vector<int> adj[MAXN];
map<pii, bool> bridge; // bridge[{u, v}] = 1 is uv is a bridge

void dfsRbc(int v, int p){
	pre[v] = lo[v] = clk++;
	int chd = 0;
	bool any = false;
	for (auto x : adj[v]){
		if (pre[x] == -1){
			chd++;
			dfsRbc(x, v);
			lo[v] = min(lo[v], lo[x]);
			if (lo[x] >= pre[v])
				any = true;
			if (lo[x] > pre[v])
				bridge[{v, x}] = bridge[{x, v}] = true;
		}
		else if (x != p)
			lo[v] = min(lo[v], pre[x]);
	}
	if (v == p and chd >= 2)
		cut[v] = true;
	if (v != p and any)
		cut[v] = true;
}

void findbc(){
	bridge.clear();
	fill(pre, pre + n + 1, -1);
	fill(cut, cut + n + 1, 0);
	clk = 0;
	for (int v = 0; v < n; v++) // 0 indexed
		if (pre[v] == -1)
			dfsRbc(v, v);
}