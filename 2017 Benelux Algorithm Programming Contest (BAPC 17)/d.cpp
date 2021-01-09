#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

//#define endl '\n'
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

const int MAXN = 1e5 + 10;

typedef pair<ll, ll> pll;

int n, m;
vector<pll> adj[MAXN];
ll dist[MAXN];

void dijkstra(int src){
	memset(dist, -1, sizeof(dist));	
	priority_queue< pll, vector<pll>, greater<pll>> pq;
	pq.push({0, src});

	ll dst, vtx;
	pll aux;
	while (!pq.empty()){
		aux = pq.top();
		pq.pop();

		dst = aux.fst; vtx = aux.snd;
		if (dist[vtx] != -1)
			continue;

		dist[vtx] = dst;
		for (auto x : adj[vtx]){
			if (dist[x.fst] == -1)
				pq.push({dst + x.snd, x.fst});
		}
	}	
}

map<pii, int> no;
bool vis[MAXN];
vi ans;

void dfs(int v){
	vis[v] = 1;
	ans.pb(v);
	if (v == 1){
		cout<<ans.size();
		for (auto x : ans)
			cout<<' '<<x;
		gnl;
		exit(0);
	}

	for (auto x : adj[v]){
		if (!vis[x.fst] and !no.count({v, x.fst}))
			dfs(x.fst);
	}

	ans.pop_back();
}

int32_t main(){
	fastio;

	cin>>n>>m;

	int a, b, c;
	fr(i, m){
		cin>>a>>b>>c;
		adj[a].pb({b, c});
		adj[b].pb({a, c});
	}

	dijkstra(1);

	for (int v = 0; v < n; v++){
		for (auto x : adj[v])
			if (dist[v] == dist[x.fst] + x.snd){
				no[{v, x.fst}] = 1;
			}
	}

	dfs(0);
	cout<<"impossible"<<endl;
}