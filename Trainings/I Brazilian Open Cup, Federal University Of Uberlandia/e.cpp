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

const ll mod = 1e9 + 7;

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
	int T;
	cin>>T;

	int n;
	while (T--){
		cin>>n;
		if (n <= 2)
			cout<<1<<endl;
		else if (n == 3)
			cout<<2<<endl;
		else{
			matrix base = { {1, 1},
							{1, 0}};

			base = fastxp(base, n - 2);
			ll ans = base[0][0] + base[0][1];
			ans %= mod;
			cout<<ans<<endl;
		}				
	}
}