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
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 5e3 + 10;
const ll mod = 1e9 + 7;

ll n, q, memo[MAXN][MAXN], sum[MAXN];

void pd(){
	memo[1][0] = 1; // numero de permutações com n elementos tal que p_i > p_{i + 1} em k posições

	for (ll i = 2; i <= n; i++){
		for (ll k = 0; k < i; k++){
			memo[i][k] = (k + 1) * memo[i - 1][k] % mod;
			if (k > 0)
				memo[i][k] = (memo[i][k] + (i - k) * memo[i - 1][k - 1]) % mod;
		}
	}

	fr(i, n){
		sum[i] = memo[n][i];
		if (i > 0)
			sum[i] = (sum[i] + sum[i - 1]) % mod;
	}

}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>q;

	pd();

	ll x;
	while (q--){
		cin>>x;	
		cout<<sum[min(x, n) - 1];
		if (q)
			cout<<' ';
	}
	gnl;

}