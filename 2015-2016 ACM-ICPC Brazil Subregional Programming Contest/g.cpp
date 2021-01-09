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
const int MAXN = 3e2 + 10;

const ll mod = 1e9 + 7;

// vou transformar o problema em achar sequencias de
// prufer com no maximo k - 1 repetições.
// pd(n, m) é quantas sequencias de tamanho m eu tenho 
// com n elementos repetindo no máximo k - 1 vezes
// https://codeforces.com/blog/entry/20335#comment-293046

ll k;
ll comb[MAXN][MAXN], memo[MAXN][MAXN];

ll pd(ll n, ll m){
	if (n == 1)
		return m < k;
	if (m == 0)
		return 1;

	ll &pdm = memo[n][m];
	if (pdm != -1)
		return pdm;

	pdm = 0;

	for (ll i = 0; i < k; i++)
		if (m >= i)
			pdm = (pdm + ((comb[m][i] * pd(n - 1, m - i)) % mod)) % mod;

	return pdm;
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	ll n;

	for (int i = 0; i < MAXN; i++){
		comb[i][0] = comb[i][i] = 1;
		for (int j = 1; j < i; j++)
			comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
	}

	cin>>n>>k;
	
	if (n <= 2){
		cout<<1<<endl;
		return 0;
	}
	if (k == 1){
		cout<<0<<endl;
		return 0;
	}

	memset(memo, -1, sizeof memo);

	cout<<pd(n, n - 2)<<endl;
}