/*
   Title: Edmond's blossom algorithm for maximum matching
   Description: Computes the maximum matching in a general graph
   Complexity:  blossom O(EV)
   
   Details: Vetices numbered from 0 to n.
   One may start with a greedy maximal matching, but I never saw a real difference.

   Credits: https://codeforces.com/profile/bicsi
*/

const int MAXN = 510; // Maximum number of vertices

int n, clk;
vector<int> adj[MAXN], match(MAXN), label(MAXN), parent(MAXN), orig(MAXN), laux(MAXN), q;

int lca(int x, int y){
	clk++;
	while(true){
		swap(x, y);
		if (x == -1) 
			continue;
		if (laux[x] == clk) 
			return x;
		laux[x] = clk;
		x = (match[x] == -1 ? -1 : orig[parent[match[x]]]);
	}
}

void blossom(int v, int w, int a){
	while (orig[v] != a){
		parent[v] = w; 
		w = match[v];
		if (label[w] == 1) 
			label[w] = 0, q.push_back(w);
		orig[v] = orig[w] = a; 
		v = parent[w];
	}
}

void augment(int v){
	while (v != -1){
		int pv = parent[v], nv = match[pv];
		match[v] = pv; 
		match[pv] = v; 
		v = nv;
	}
}

int bfs(int root){
	fill(label.begin(), label.begin() + n, -1);
	iota(orig.begin(), orig.begin() + n, 0);
	q.clear(); 
	q.push_back(root);
	label[root] = 0; 
	for (int i = 0; i < (int)q.size(); ++i){
		int v = q[i];
		for (auto &x : adj[v]){
			if (label[x] == -1){
				label[x] = 1; 
				parent[x] = v;
				if (match[x] == -1) 
					return augment(x), 1;
				label[match[x]] = 0; 
				q.push_back(match[x]);
			} else if (label[x] == 0 and orig[v] != orig[x]){
				int a = lca(orig[v], orig[x]);
				blossom(x, v, a); 
				blossom(v, x, a);
			}
		}
	}
	return 0;
}
 
int blossom(){
	clk = -1;
	fill(match.begin(), match.begin() + n, -1);
	fill(laux.begin(), laux.begin() + n, -1);
	int res = 0;
	
	for (int i = 0; i < n; i++) 
		if (match[i] == -1 and bfs(i))
			res++;
	return res;
}
