/*Computes the min. cost subgraph connecting all terminals
Complexity: O((2**t) * (n**2) + (3**t) * n)
Computes the cost of a tree that connects each subset of 
terminals with a given root. One may use this information to 
build a forest.
Terminals as leafs:ignore the terminal vertices in the 
graph, ie, skip them in the for loops.*/
int stein[1<<NTERM][MAXN]; // stein[mask][v] is the least 
// cost tree rooted at v connecting all terminals in mask
int steiner_pd(){
	memset(stein, INF, sizeof stein);
	// terminals are the first nterm vertices

	for (int v = 0; v < n; v++) // 0 indexed
		for (int t = 0; t < nterm; t++)
			stein[1<<t][v] = dist(v, t);
	
	for (int msk = 1; msk < (1 << nterm); msk++) //terminals
		for (int v = 0; v < n; v++){ // root
			for (int smsk = (msk - 1)&msk; smsk > 0; 
												smsk = (smsk - 1) & msk)
				stein[msk][v] = min(stein[msk][v], 
							stein[smsk][v] + stein[msk^smsk][v]);
			for (int u = 0; u < n; u++) // reroot
				stein[msk][u] = min(stein[msk][u], 
										stein[msk][v] + dist(u, v));	
		}	

	int ans=*min_element(stein[(1<<k)-1],stein[(1<<k)-1]+n);

	return ans;	
}