/*
   Title: Steiner Tree DP
   Description: Computes the optimal cost subgraph that connects all terminals
   Complexity: O((2**t) * (n**2) + (3**t) * n)
   	
   Details: Computes the cost of a tree that connects each subset of terminals
   with a given vertex as root. One may use this information to build a forest.

   If one need the vertices to be leafs, one just need to ignore the terminal
   vertices in the graph, ie, skip them in the for loops.

   Here, dist(v, u) returns the distance between these vertices. One may compute
   this with the Floyd-Warshall algorithm.	

*/

const int INF = 0x3f3f3f3f;
const int MAXN = 1e3 + 10;
const int NTERM = 10;

int stein[1<<NTERM][MAXN]; // stein[mask][v] is the least cost of a tree 
			   // rooted at v that connects all terminals in the mask

int steiner_pd(){
	memset(stein, INF, sizeof stein);
	// Here we consider the terminals to be the first nterm vertices, in
	// the general case one must map these to vertices in the graph

	for (int v = 0; v < n; v++) // 0 indexed
		for (int t = 0; t < nterm; t++)
			stein[1<<t][v] = dist(v, t); // distance between v and terminal t
	
	for (int msk = 1; msk < (1 << nterm); msk++) // Set of terminals
		for (int v = 0; v < n; v++){ // root
			for (int smsk = (msk - 1)&msk; smsk > 0; smsk = (smsk - 1) & msk)
				stein[msk][v] = min(stein[msk][v], stein[smsk][v] + stein[msk^smsk][v]);
			for (int u = 0; u < n; u++) // reroot
				stein[msk][u] = min(stein[msk][u], stein[msk][v] + dist(u, v));	
		}	

	int ans = *min_element(stein[(1<<k) - 1], stein[(1<<k) - 1] + n); // smallest cost

	return ans;	
}
