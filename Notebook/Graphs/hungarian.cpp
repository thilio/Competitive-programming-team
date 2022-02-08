/*
   Title: Kuhn's algorithm for optimal perfect matching in bip. graph (Hungarian Method)
   Description: Computes the optimal perfect matching in a bip. graph
   Complexity:  hungarian O(V^3)
   
   Details: Vetices indexed from 0 to max(n, m) - 1 on both sides.

   Since it is a primal-dual method, z and y are a solution 
   for the dual problem (written for primal maximization)

		Minimize 			z.ones(n) + y.ones(m),
			S.t 	z[i] + y[j] >= cst(i, j) for (i, n) \in ([n], [m]).

	The dual problem for mizimization is maximization with <=.

   Credits: https://github.com/mhunicken/icpc-team-notebook-el-vasito
*/

using coord = double; // Data type
const int MAXN = 500; // Maximum number of vertices
const coord INF = 1e100; // For maximazation, make INF = 0 and negate costs

bool zero(coord x){ return fabs(x) < 1e-9; } // Use x == 0 for int/ll

int N, matchl[MAXN], matchr[MAXN]; // Size of the graph, and the matching
coord cst[MAXN][MAXN]; // Cost matrix

void init(int n, int m){ // Left size, right size
	N = max(n, m);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cst[i][j] = (i < n and j < m) ? INF : 0;
}

void add(int x, int y, coord c){ cst[x][y] = c; }

coord hungarian(){
	int mat = 0, dad[MAXN], vis[MAXN];
	coord ds[MAXN], y[MAXN], z[MAXN]; // Dual solution

	for (int i = 0; i < N; i++)
		y[i] = *min_element(cst[i], cst[i] + N);
	
	for (int j = 0; j < N; j++){
		z[j] = cst[0][j] - y[0];
		for (int i = 1; i < N; i++)
			z[j] = min(z[j], cst[i][j] - y[i]);
	}
	
	memset(matchl, -1, sizeof matchl);
	memset(matchr, -1, sizeof matchr);

	for (int i = 0; i < N; i++) // Speedup
		for (int j = 0; j < N; j++)
			if (matchr[j] == -1 && zero(cst[i][j] - y[i] - z[j])){
				matchl[i] = j;
				matchr[j] = i;
				mat++;
				break;
			}

	while (mat < N){
	    int s = 0, j = 0, i;
	    while (matchl[s] != -1)
	    	s++;

	    memset(dad, -1, sizeof dad);
	    memset(vis, 0, sizeof vis);

	    for (int k = 0; k < N; k++)
	    	ds[k] = cst[s][k] - y[s] - z[k];
	    
	    while (true){
	        j = -1;
	        for (int k = 0; k < N; k++)
	        	if (!vis[k] && (j == -1 || ds[k] < ds[j]))
	        		j = k;
	        
	        vis[j] = 1; 
	        i = matchr[j];
	        if (i == -1) 
	        	break;

	        for (int k = 0; k < N; k++)
		        if (!vis[k]){
		            auto new_ds = ds[j] + cst[i][k] - y[i] - z[k];
		            if(ds[k] > new_ds){
		            	ds[k] = new_ds;
		            	dad[k] = j;
		            }
		        }
	    }

	    for (int k = 0; k < N; k++)
		    if (k != j && vis[k]){
		    	auto w = ds[k] - ds[j];
		    	z[k] += w;
		    	y[matchr[k]] -= w;
		    }
	  
	    y[s] += ds[j];
	  
	    while (dad[j] >= 0){
	    	int d = dad[j]; 
	    	matchr[j] = matchr[d]; 
	    	matchl[matchr[j]] = j; 
	    	j = d;
	    }

	    matchr[j] = s; 
	    matchl[s] = j;
	    mat++;
	}
	
	coord value = 0;
	for (int i = 0; i < N; i++)
		value += cst[i][matchl[i]];
	return value;
}
