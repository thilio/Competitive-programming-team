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
const int MOD = 1e9+7;

int n, m, L, U;
pii edge[100100];
vector<pii> adj[100100];

int dist[100100];

void dijkstra(int v){
	priority_queue<pii, vector<pii>, greater<pii>> pq;

	ms(dist, -1);
	//dist[v] = 0;

	pq.push({0, v});
	while(!pq.empty()){
		int u, w;
		tie(w, u) = pq.top();
		pq.pop();
		if(dist[u] != -1) continue;
		dist[u] = w;

		for(auto x: adj[u]){
			if(dist[x.fst] == -1){
				pq.push({w + x.snd, x.fst});
			}
		}
	}

}

int main(){

	fastio;	
	cin >> n >> m >> L >> U;

	fr(i, m){
		ll u, v, w;
		cin >> u >> v >> w;
		adj[u].pb({v, w});
		adj[v].pb({u, w});
		edge[i] = {u, v};
	}	

	dijkstra(0);
	//fr(i, n) dbg(dist[i]);

	int ans = 0;
	fr(i, m){
		int mn = min(dist[edge[i].fst], dist[edge[i].snd]);

		if(mn < (U + 1)/2) ans++;
	}

	cout << ans << endl;


}
