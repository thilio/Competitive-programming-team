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
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));
#define db cout << "Debug" << endl;
#define all(x) begin(x), end(x)
#define dbg(x)  cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000000

ll r, s, m, d, n;
ll adj[100][100];

ll brands[1010];
vector<ll> dish[100];

ll prod(ll a, ll b){
	__int128 x = a, y = b;
	if(x*y > INF){
		cout << "too many" << endl;
		exit (0);
	}
	return (ll)(x*y);
}

ll sum(ll a, ll b){
	__int128 x = a, y = b;
	if(x + y > INF){
		cout << "too many" << endl;
		exit (0);
	}
	return (ll)(x + y);
}

ll solve(ll a, ll b, ll c){
	set<ll> ing;
	if(adj[a][b] || adj[a][c] || adj[b][c]) return 0;

	for(auto x: dish[a]) ing.insert(x);
	for(auto x: dish[b]) ing.insert(x);
	for(auto x: dish[c]) ing.insert(x);
	
	ll ret = 1;
	for(auto x: ing){
		ret = prod(ret, brands[x]);
	}
	return ret;
}

void read(){
	cin >> r >> s >> m >> d >> n;
	frr(i, r) cin >> brands[i];
	frr(i, s + m + d){
		ll k;
		cin >> k;
		fr(j, k){
			ll x;
			cin >> x;
			dish[i].pb(x);
		}
	}
	fr(i, n){
		ll u, v;
		cin >> u >> v;
		adj[u][v] = 1;
		adj[v][u] = 1;
	}
}

int main(){
	fastio;
	read();
	ll ans = 0;
	for(ll i = 1; i <= s; i++){
		for(ll j = s + 1; j <= s + m; j++){
			for(ll k = s + m + 1; k <= s + m + d; k++){
				ans = sum(ans, solve(i, j, k));
			}
		}
	}
	cout << ans << endl;
}
