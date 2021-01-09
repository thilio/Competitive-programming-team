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
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 2e2 + 10;

const ll mod = 1e9 + 7;

typedef vector< vector<ll> > matrix;

matrix operator*(matrix a, matrix b){
	matrix c(a.size(), vector<ll>(b[0].size(), 0));
	for (int i = 0; i < a.size(); i++){
		for (int j = 0; j < b[0].size(); j++){
			for (int k = 0; k < b.size(); k++)
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
		}
	}
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

ll fastxp(ll base, ll exp){
	ll ans = 1;
	while (exp){
		if (exp & 1)
			ans = (ans * base) % mod;
		base = (base * base) % mod;
		exp >>= 1;
	}
	return ans;
}

ll n, k, m, v[MAXN];

int32_t main(){
	fastio;

	cin>>n>>k>>m;

	frr(i, k)
		v[i % m]++;
	v[0] = 0;

	matrix base(m, vector<ll>(m));	

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			base[i][(i - j + m) % m] = v[j];

	base = fastxp(base, n - 1);

	ll zero, tot;
	zero = tot = 0;

	for (int j = 0; j < m; j++)
		zero = (zero + base[0][j] * v[j]) % mod;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			tot = (tot + base[i][j] * v[j]) % mod;	

	ll ans = (zero * fastxp(tot, mod - 2)) % mod;

	cout<<ans<<endl;
}