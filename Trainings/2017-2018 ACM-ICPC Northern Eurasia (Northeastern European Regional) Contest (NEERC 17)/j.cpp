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
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 3e3 + 10;


// Resolve o problema do caminho mínimo quando só se paga
// as k arestas mais caras do caminho em O(m²log(m)).

typedef pair<ll, ll> pll;
	
ll n, m, k;
vector<pll> adj[MAXN];

ll dist[MAXN];
ll dij(ll val){
	memset(dist, -1, sizeof dist);
	priority_queue<pll, vector<pll>, greater<pll>> fila;
	fila.push({0, 1});

	ll vtx, dst, cst;
	while (!fila.empty()){
		tie(dst, vtx) = fila.top();
		fila.pop();

		if (dist[vtx] != -1)
			continue;
		dist[vtx] = dst;
		for (auto x : adj[vtx])
			if (dist[x.fst] == -1){
				cst = max(0ll, x.snd - val);
				fila.push({cst + dst, x.fst});
			}
	}

	return dist[n] + val * k;
}

int32_t main(){
	fastio;
	cin>>n>>m>>k;

	ll a, b, c;
	fr(i, m){
		cin>>a>>b>>c;
		adj[a].pb({b, c});
		adj[b].pb({a, c});
	}

	ll ans = dij(0);

	frr(v, n)
		for (auto x : adj[v])
			ans = min(ans, dij(x.snd));
	cout<<ans<<endl;
}