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
const int MAXN = 5e3 + 10;
const ll mod = 1e9 + 9;

ll n, v[MAXN];
ll p[MAXN], cmb[MAXN][MAXN], invmod[MAXN];

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

int32_t main(){
	fastio;

	cin>>n;
	frr(i, n)
		cin>>v[i];

	sort(v + 1, v + n + 1);
	
	ll cnt;

	for (int i = 1; i < MAXN; i++) // pre-calcula invmod
		invmod[i] = fastxp(i, mod - 2);

	// calcula as permutações dos elementos de i - j cmb[i][j]
	for (int k = 0; k <= n; k++){
		cmb[k][k] = 1;
		
		cnt = 1;
		for (ll l = k + 1; l <= n; l++){
			if (l > k + 1 and v[l] == v[l - 1])
				cnt++;
			else	
				cnt = 1;
			cmb[k][l] = (((cmb[k][l - 1] * (l - k)) % mod) * invmod[cnt]) % mod;
		}
	}


	ll aux;
	p[0] = 1;	
	for (ll k = 1; k <= n; k++){ // p[k] é o # de sequências desordenadas de a_1 até a_k-1
		aux = 0;
		for (ll i = 1; i <= k; i++)
			aux = (aux + ((p[i - 1] * cmb[i][k]) % mod)) % mod;

		p[k] = (cmb[0][k] - aux + mod) % mod;	
	}

	cout<<p[n]<<endl;
}