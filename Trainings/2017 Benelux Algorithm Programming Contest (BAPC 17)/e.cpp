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
const int MAXN = 1e3 + 10;

typedef pair<ll, ll> pll;

vector<int> adju[MAXN]; // adj da partição U
int matchu[MAXN], matchv[MAXN]; 
int dist[MAXN], q[MAXN];
int m, n;

bool bfs(){
	int st = 0, en = 0;
	for (int u = 1; u <= m; u++){
		if (matchu[u] == 0){
			dist[u] = 0; 
			q[en++] = u;
		}
		else dist[u] = INF;
	}
	dist[0] = INF;
	while (en > st){
		int u = q[st++];
		if (dist[u] >= dist[0]) 
			continue;
		for (int v : adju[u]){
			if (dist[matchv[v]] == INF){
				dist[matchv[v]] = dist[u] + 1;
				q[en++] = matchv[v];
			}
		}
	}

	return (dist[0] != INF);
}

bool dfs(int u){
	if (u == 0) return true;
	for (int v : adju[u]){
		if (dist[matchv[v]] == dist[u] + 1){
			if (dfs(matchv[v])){
				matchv[v] = u; 
				matchu[u] = v;
				return true;
			}
		}
	}
	dist[u] = INF;
	return false;
}

int hopcroftKarp(){
	memset(&matchu, 0, sizeof matchu);
	memset(&matchv, 0, sizeof matchv);
	int result = 0;
	while (bfs()){
		for (int u = 1; u <= m; u++){
			if (matchu[u] == 0 and dfs(u))
				result++;
		}
	}
	return result;
}

int egg;
vector<pll> adj[MAXN], b, r;
vector<ll> edge;

ll dist2(int x, int y){
	return (b[x].fst - r[y].fst)*(b[x].fst - r[y].fst) + (b[x].snd - r[y].snd)*(b[x].snd - r[y].snd);
}

bool test(ll val){
	for(int i = 1; i <= m; i++){
		adju[i].clear(); //limpei o grafo do hop
		for (auto x : adj[i]){ // grafo original
			if (x.fst < val)
				adju[i].pb(x.snd);// botei no grafo do hop
		}
	}

	return (n + m - hopcroftKarp()) >= egg;
}

int32_t main(){
	fastio;
	cin>>egg>>m>>n; // vou emparelhar a partir de B

	ll x, y;
	fr(i, m){
		cin>>x>>y;
		b.pb({x, y});
	}

	fr(i, n){
		cin>>x>>y;
		r.pb({x, y});
	}

	fr(i, m){
		fr(j, n){
			adj[i + 1].pb({dist2(i, j), j + 1});
			edge.pb(dist2(i, j));
		}
	}

	sort(all(edge));

	int ini, fim, meio, best;
	ini = best = 0;
	fim = m * n - 1;

	while (ini <= fim){
		meio = (ini + fim)/2;

		if (test(edge[meio])){
			best = meio;
			ini = meio + 1;
		}
		else
			fim = meio - 1;
	}

	cout<<setprecision(12)<<fixed;
	cout<< sqrt(edge[best]) <<endl;
}