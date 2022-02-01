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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 3e5 + 10;

int n, m, s, t;
int dist[MAXN], deg[MAXN], bdst[MAXN];
vii adj[MAXN];

void dij(){
	fill(dist, dist + MAXN, -1);

	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0, 2 * t}); // blue
	pq.push({0, 2 * t + 1}); // red

	int dst, vtx;
	while (!pq.empty()){
		tie(dst, vtx) = pq.top();
		pq.pop();

		if (dist[vtx] != -1) // already relaxed, skip
			continue;

		dist[vtx] = dst;

		for (auto x : adj[vtx]){
			if (vtx & 1){ // red
				bdst[x.fst] = max<ll>(bdst[x.fst], dst + x.snd); // max dist found

				deg[x.fst]--;
				if (deg[x.fst] == 0) // relaxed all red parents
					pq.push({bdst[x.fst], x.fst}); // insert blue on pq
			}
			else{ // blue
				if (dist[x.fst] == -1) // min dist
					pq.push({dst + x.snd, x.fst}); // pq find minimum
			}			
		}
	}
}

int32_t main(){
	fastio;
	cin>>n>>m>>s>>t;

	int v, u, w;
	fr(i, m){
		cin>>v>>u>>w;
		adj[2 * u].pb({2 * v + 1, w}); // blue -> red
		adj[2 * u + 1].pb({2 * v, w}); // red -> blue
		deg[2 * v]++;
		deg[2 * v + 1]++;
	}

	dij();

	if (dist[2 * s] == -1)
		cout<<"infinity"<<endl;
	else
		cout<<dist[2 * s]<<endl;
}