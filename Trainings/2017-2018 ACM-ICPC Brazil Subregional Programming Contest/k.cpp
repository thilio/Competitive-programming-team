#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

const ll mod = 1e5;

typedef vector< vector<ll> > matrix;

matrix operator*(matrix a, matrix b){
	matrix c(a.size(), vector<ll>(b[0].size(), 0));
	for (int i = 0; i < a.size(); i++)
		for (int k = 0; k < b.size(); k++) // paginação do C, acelera o produto
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

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	ll a, b, n, k;
	cin>>a>>b>>n>>k;

	matrix base = {
		{a, b},
		{1, a}
	};

	base = fastxp(base, n);

	ll x = base[0][0];

	x = (2 * x) % mod;

	if ((a * a == b) or (a * a < b and n % 2))
		x++;

	x = (x - 1 + mod) % mod;

	fr(i, k - 1)
		x /= 10;

	cout<<x%10<<endl; 
}