#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 998244353;

vi adj[100100];
ll sz[100100];
int pai[100100];

ll fast(ll base, ll exp){
	if(exp == 0) return 1;
	ll ans = fast(base,exp/2);
	ans *= ans;
	ans%=MOD;
	if(exp&1) ans *= base;
	ans%= MOD;
	return ans;
}

ll invmod(ll x){
	return fast(x,MOD - 2);
}

void dfs(int v){
	for(auto x: adj[v]) dfs(x);
	for(auto x: adj[v]) sz[v] += sz[x];
	sz[v]++;
}

int main(){

	fastio;
	int n;
	cin >> n;

	if(n == 1){
		cout << 0 << endl;
		return 0;
	}

	for(int i = 2; i <= n; i++){
		int x;
		cin >> x;
		adj[x].pb(i);
		pai[i] = x;
	}

	dfs(1);
	ll ans = 0;
	for(int i = 2; i <= n; i++){
		ll termo = 1;
		termo *= (sz[pai[i]] - 1 - sz[i]);
		termo %= MOD;
		termo *= invmod(sz[pai[i]] - 1);
		termo %= MOD;
		termo *= sz[i];
		termo %= MOD;
		termo *= invmod(n);
		termo %= MOD;

		ans = (ans + termo)%MOD;
	}

	cout << ans << endl;



}
