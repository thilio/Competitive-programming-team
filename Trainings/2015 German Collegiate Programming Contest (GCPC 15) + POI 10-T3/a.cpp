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

ll wond[30];
ll dp[(1 << 16)][30][2];
ll dist[30][MAXN];
ll n, p, m, tot, taxi;
ll t[30];
vector<pii> adj[MAXN];

void solveDP(){
	fr(i, 30){
		fr(j, (1 << 16)) dp[j][i][0] = dp[j][i][1] = MOD;
	}

	for(ll v = 0; v < p; v++){
		//cout << (1 << v) << " " <<v  << " " << 0 << " " << dist[p][wond[v]] << " " << wond[v] << endl;
		dp[(1 << v)][v][0] = dist[p][wond[v]] + t[v];
		dp[(1 << v)][v][1] = taxi + t[v];
	}

	for(ll mask = 0; mask < (1 << p); mask++){
		for(ll v = 0; v < p; v++){
			if(((1 << v) & mask) == 0) continue;

			for(ll b = 0; b < p; b++){
				if(b == v) continue;

				if((1 << b) & mask){
					dp[mask][v][0] = min(dp[mask][v][0], dp[(mask ^ (1 << v))][b][0] + dist[b][wond[v]] + t[v]);
					dp[mask][v][1] = min(dp[mask][v][1], dp[(mask ^ (1 << v))][b][1] + dist[b][wond[v]] + t[v]);
					dp[mask][v][1] = min(dp[mask][v][1], dp[(mask ^ (1 << v))][b][0] + taxi + t[v]);
				}
			}
		}
	}
}

void dijkstra(ll v, ll ind){
	fr(i, n) dist[ind][i] = MOD;
	pq<pii, vector<pii>, greater<pii>> fila;
	fila.push({0, v});

	while(true) {
		ll davez = -1;
		while(fila.size()){
			ll u = fila.top().s;
			ll d = fila.top().f;
			fila.pop();

			if(dist[ind][u] == MOD){
				dist[ind][u] = d;
				davez = u;
				break;
			}
		}

		if(davez == -1) break;

		//cout << davez << endl;

		for(auto x : adj[davez]){
			ll u = x.f, w = x.s;
			if(dist[ind][u] == MOD){
				fila.push({dist[ind][davez] + w, u});
			}
		}
	}
	/*
	cout << v << endl;
	fr(i, n) cout << dist[ind][i] << " ";
	cout << endl;
	*/
}

void build(){
	cin >> n >> p >> m >> tot >> taxi;
	fr(i, p) {
		cin >> wond[i] >> t[i];
	}
	fr(i, m){
		ll u, v, w;
		cin >> u >> v >> w;
		adj[u].pb({v, w});
		adj[v].pb({u, w});
	}

	fr(i, p) dijkstra(wond[i], i);
	dijkstra(0, p);
}

int main(){
	fastio;

	build();
	solveDP();

	ll deu = 0;
	for(ll i = 0; i < p; i++){
		if(dp[(1 << p) - 1][i][0] + dist[i][0] <= tot){
			cout << "possible without taxi" << endl;
			return 0;
		}
	}

	for(ll i = 0; i < p; i++){
		if(dp[(1 << p) - 1][i][1] + dist[i][0] <= tot){
			cout << "possible with taxi" << endl;
			return 0;
		}
	}

	cout << "impossible" << endl;
}
