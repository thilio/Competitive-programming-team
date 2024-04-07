/* Knuth DP optimization
Finds the best order to split an array in n points O(n^2)

We can optimize this naive DP
pd(i, j) = min_{i<k<j} {pd(i,k) + pd(k,j)} + c[i][j], O(n^3)
If A[i][j-1]<=A[i][j]<=A[i + 1][j], where A[i][j] is a opt. 
split point(k from the rec.) for the interval v[i...j].
Suff. cond: C[a][c]+C[b][d]<=C[a][d]+C[b][c], a<=b<=c<=d.
                     C[b][c] <= C[a][d]

Problem: find the best order to split a string of size n in 
m given points where the cost of splitting at i is the size 
of the current interval containing i.*/
int n, m, cuts[MAXN], memo[MAXN][MAXN], mid[MAXN][MAXN];
int pd(){
	for (int sz = 0; sz <= m; sz++){ // size of interval
		for (int l = 0; l <= m - sz; l++){
			int r = l + sz;
			if (sz < 2)
				memo[l][r] = 0, mid[l][r] = l, continue;
			
			int midl = mid[l][r - 1], midr = mid[l + 1][r];
			memo[l][r] = INF; mid[l][r] = l;
			for (int k = midl; k <= midr; k++){ // all splits
				int aux = memo[l][k]+memo[k][r]+cuts[r]-cuts[l];
				if (memo[l][r] > aux)
					memo[l][r] = aux, mid[l][r] = k;
			}
		}
	}
	return memo[0][m];
}
/*cuts[i] - ith splitting point. cuts[m + 1] = n*/