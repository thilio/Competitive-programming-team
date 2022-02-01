#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

#define int ll

typedef tuple<int, int, int> tup;

int n, m, a, b, k;

int start[2];
int dist[2][MAXN][11];
int distr[2][MAXN][11];

vii adj[MAXN], adjr[MAXN];

void dijkstra(int ini){
	fr(i, MAXN)
		fr(j, 11)
			dist[ini][i][j] = INF;

	priority_queue< tup, vector<tup>, greater<tup> > pq;
	pq.push({0, 0, start[ini]});

	int dst, tkt, vtx;

	while (!pq.empty()){
		tie(dst, tkt, vtx) = pq.top();
		pq.pop();

		if (dist[ini][vtx][tkt] != INF)
			continue;

		dist[ini][vtx][tkt] = dst;

		for (auto x : adj[vtx]){
			if (tkt < k and dist[ini][x.fst][tkt + 1] == INF)
				pq.push({dst, tkt + 1, x.fst});
			if (dist[ini][x.fst][tkt] == INF)
				pq.push({dst + x.snd, tkt, x.fst});
		} 
	}		
}

void dijkstrar(int ini){
	fr(i, MAXN)
		fr(j, 11)
			distr[ini][i][j] = INF;
			
	priority_queue< tup, vector<tup>, greater<tup> > pq;
	pq.push({0, 0, start[ini]});

	int dst, tkt, vtx;

	while (!pq.empty()){
		tie(dst, tkt, vtx) = pq.top();
		pq.pop();

		if (distr[ini][vtx][tkt] != INF)
			continue;

		distr[ini][vtx][tkt] = dst;

		for (auto x : adjr[vtx]){
			if (tkt < k and distr[ini][x.fst][tkt + 1] == INF)
				pq.push({dst, tkt + 1, x.fst});
			if (distr[ini][x.fst][tkt] == INF)
				pq.push({dst + x.snd, tkt, x.fst});
		} 
	}		
}

int32_t main(){
	fastio;
	cin>>n>>m>>a>>b>>k;

	start[0] = a;
	start[1] = b;

	int u, v, w;
	fr(i, m){
		cin>>u>>v>>w;
		adj[u].pb({v, w});
		adjr[v].pb({u, w});
	}
	
	fr(i, 2){
		dijkstra(i); // u -> todos
		dijkstrar(i); // todos -> u
	}

	int vtx = -1, dst = INF;
	int aux;

	for (int v = 0; v < n; v++ ){
		if (v == a or v == b)
			continue;

		for (int i = 1; i <= k; i++){
			dist[0][v][i] = min(dist[0][v][i], dist[0][v][i - 1]);
			dist[1][v][i] = min(dist[1][v][i], dist[1][v][i - 1]);
			distr[0][v][i] = min(distr[0][v][i], distr[0][v][i - 1]);
			distr[1][v][i] = min(distr[1][v][i], distr[1][v][i - 1]);
		}

		for (int i = 0; i <= k; i++)
			for (int j = 0; j <= k; j++){
				aux = dist[0][v][i] + distr[0][v][k - i] + dist[1][v][j] + distr[1][v][k - j];
				if (aux < dst){
					vtx = v;
					dst = aux;
				} 
			}
	}

	if (vtx == -1)
		cout<<">:("<<endl;
	else
		cout<<vtx<<' '<<dst<<endl;		
}