#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(ll i = 0; i < n; i++)
#define frr(i, n) for(ll i = 1; i <= n; i++)
#define frm(i, n) for(ll i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<ll,ll> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

ll pr[MAXN], nxt[MAXN], fr[MAXN];
ll n;

void dfs(ll v){
	ll davez = nxt[v];
	pr[v] = 1;
	ll sz = 1;

	while(davez != v) {
		pr[davez]++;
		davez = nxt[davez];
		sz++;
	}

	fr[sz]++;
}

ll dp[MAXN], fat[MAXN];
void build(){
	cin >> n;
	fr(i, n) cin >> nxt[i];
	fr(i, n){
		if(!pr[i]) dfs(i);
	}	
}

ll solveEven(ll x, ll tam){
	if(x == 0) return 1;
	if(x%4 != 0) {
		cout << 0 << endl;
		exit (0);
	}
	dp[0] = 1;

	for(ll i = 4; i <= x; i+=4){
		dp[i] = ((i-1)*(i-2)*(i-3))%MOD;
		ll aux = (tam*tam*tam)%MOD;
		dp[i] = (aux*dp[i])%MOD;
		dp[i] = (dp[i-4]*dp[i])%MOD;
	}

	return dp[x];
}

ll solveOdd(ll x, ll tam){
	fr(i, x + 1) dp[i] = 0;
	dp[0] = 1;
	dp[1] = 1;
	dp[2] = 1 + tam;
	dp[3] = 1 + 3*tam;

	for(ll i = 4; i <= x; i++){
		dp[i] = ((i-1)*(i-2)*(i-3))%MOD;
		ll aux = (tam*tam*tam)%MOD;
		dp[i] = (aux*dp[i])%MOD;
		dp[i] = (dp[i-4]*dp[i])%MOD;

		//cout << dp[i] << endl;
		dp[i] = (dp[i] + ((i-1)*tam*dp[i-2])%MOD + dp[i-1])%MOD;
		//cout << ((i-1)*tam*dp[i-2])%MOD << endl;
	}

	return dp[x];
}


int main(){
	fastio;
	build();
	ll ans = 1;

	frr(i, n){
		if(i%2 == 0) ans = (ans * solveEven(fr[i], i))%MOD;
		else ans = (ans * solveOdd(fr[i], i))%MOD;
	}
	/*	
	fr(i, 6){
		cout << solveOdd(i) << endl;
	}
	*/

	cout << ans << endl;
}
