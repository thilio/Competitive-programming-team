/*
    Title: Fast exponentiation of numbers and matricies
	Complexity: O(n^3log(exp))
	Details: In the matrix case, recursive exponentiation may perform better.
*/
const ll mod = 1e9 + 7;

typedef vector< vector<ll> > matrix;

matrix operator*(matrix const &a, matrix const &b){
	matrix c(a.size(), vector<ll>(b[0].size(), 0));
	for (int i = 0; i < a.size(); i++)
		for (int k = 0; k < b.size(); k++)
			for (int j = 0; j < b[0].size(); j++)
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
	return c;
}

matrix getid(int n){
	matrix id(n, vector<ll>(n, 0));
	for (int i = 0; i < n; i++)
		id[i][i] = 1;
	return id;
}

matrix fastxp(matrix base, ll exp){
	matrix ans = getid(base.size());
	while (exp){
		if (exp & 1)
			ans = ans * base;
		base = base * base;
		exp >>= 1;
	}
	return ans;
}
