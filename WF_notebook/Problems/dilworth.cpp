/* Dilworth's theorem for poset covering
Finds the largest atichain of a poset on O(n^3)
Atichain: set of elements that cant be compared
Use with any max matching algorith, which finds min cover*/
int madj[MAXN][MAXN]; // adjacency of the graph
void dilworth(){
	for (int k = 1; k <= n; k++) // transitive closure
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				madj[i][j] |= madj[i][k] & madj[k][j];

	for (int i = 1; i <= n; i++)//dilworth's bip graph
		for (int j = 1; j <= n; j++)
			if (madj[i][j] and i != j)
				adju[i].push_back(j);

	cout<<(n - HopcroftKarp())<< endl;//|longest antichain|			
// v is in the antichain if both copies aren't in min cover
	for (int i = 1; i <= n; i++)
		if (coveru[i] == 0 and coverv[i] == 0)
			cout<<i<<' '; // in the antichain
	cout<<endl;	
}
