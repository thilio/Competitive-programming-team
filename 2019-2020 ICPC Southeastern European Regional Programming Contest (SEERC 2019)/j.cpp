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
#define INF 1000000000000000100

ll n;
vector<ll> adj[MAXN];

int main(){
	fastio;
	cin >> n;
	fr(i, n*(n-1)/2){
		ll u, v, w;
		cin >> u >> v >> w;
		adj[v].pb(w);
		adj[u].pb(w);
	}

	ll ans = 0;
	frr(i, n){
		sort(all(adj[i]));
		for(ll j = 0; j < n-1; j += 2){
			ans += adj[i][j+1];
		}
	}
	cout << ans << endl;
}
