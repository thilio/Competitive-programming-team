/*
	Title: Segment Tree 2D
	Description: Data structure to make range queries in R2
	Complexity: 
		- build: O(n * m)
		- update: O(log^2 n)
		- query: O(log^2 n)
*/

#define fr(i, n) for(int i = 0; i < n; i++)
struct SEG2D{
	int n, m;
	vector<vector<int>> st;
	const int NEUT = MOD; // 0 para soma, INF para min

	int op(int a, int b){return min(a, b);}
	SEG2D(vector<vector<int>> a = {}){
		n = a.size(), m = (n ? a[0].size() : 0);
		st.resize(2 * n);
		fr(i, 2 * n) st[i].resize(2 * m);
		fr(i, n) fr(j, m) st[i + n][j + m] = MOD;
		
		fr(i, n) for(int j = m - 1 ; j > 0; j--)
			st[i + n][j] = op(st[i + n][j << 1], st[i + n][j << 1 | 1]);
		for(int i = n - 1; i > 0; i--) fr(j, 2*m)
			st[i][j]=op(st[i<<1][j],st[i<<1|1][j]);
	}
	// intervalo aberto
	void update(int x, int y, int v){
		st[x + n][y + m]=v;
		for(int j = y + m;j > 1;j >>= 1)
			st[x + n][j >> 1] = op(st[x + n][j], st[x + n][j ^ 1]);
		for(int i = x + n; i > 1;i >>= 1)
			for(int j = y + m; j ; j >>= 1)
				st[i >> 1][j] = op(st[i][j], st[i^1][j]);
	}
	// intervalo aberto
	int query(int x0, int x1, int y0, int y1){
		int r = NEUT;
		for(int i0 = x0 + n,i1 = x1 + n; i0 < i1; i0 >>= 1, i1 >>= 1){
			int t[4],q = 0;
			if(i0&1) t[q++] = i0++;
			if(i1&1) t[q++] = --i1;
			fr(k, q){ 
				for(int j0 = y0 + m,j1 = y1 + m;j0 < j1; j0 >>= 1,j1 >>= 1){
					if(j0&1)r = op(r, st[t[k]][j0++]);
					if(j1&1)r = op(r, st[t[k]][--j1]);
				}
			}
		}
		return r;
	}
};
