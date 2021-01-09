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
typedef pair<ll, ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   

#define int long long int /////////////////////////


const int MAXN = 1e5 + 3000;
const int MAXM = 4e6;

int ned, first[MAXN], work[MAXN], dist[MAXN], q[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM];

void init(){
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, int f){
	to[ned] = v, cap[ned] = f;
	nxt[ned] = first[u];
	first[u] = ned++;
	
	to[ned] = u, cap[ned] = 0;
	nxt[ned] = first[v];
	first[v] = ned++;
}

int dfs(int u, int f, int t){
	if (u == t) return f;
	for (int &e = work[u]; e != -1; e = nxt[e]){
		int v = to[e];
		if (dist[v] == dist[u] + 1 && cap[e] > 0){
			int df = dfs(v, min(f, cap[e]), t);
			if (df > 0){
				cap[e] -= df;
				cap[e^1] += df;
				return df;
			}
		}
	}
	return 0;
}

bool bfs(int s, int t){
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	int st = 0, en = 0;
	q[en++] = s;
	while (en > st){
		int u = q[st++];
		for (int e = first[u]; e != -1; e = nxt[e]){
			int v = to[e];
			if (dist[v] < 0 && cap[e] > 0){
				dist[v] = dist[u] + 1;
				q[en++] = v;
			}
		}
	}
	return dist[t] >= 0;
}

int dinic(int s, int t){
	int flow = 0, f;
	while (bfs(s, t)){
		memcpy(work, first, sizeof work);
		while (f = dfs(s, INF, t)) 
			flow += f;
	}
	return flow;
}

ll n, m, s, p[MAXN]; 
ll l[11], c[11];
vector<pll> adj[MAXN];

ll d[11][MAXN];
void dij(int src){
	fr(i, MAXN) 
		d[src][i] = -1;
	
	priority_queue<pll, vector<pll>, greater<pll> > pq;
	pq.push({0, l[src]});

	ll vtx, dst;
	while (!pq.empty()){
		dst = pq.top().fst;
		vtx = pq.top().snd;
		pq.pop();

		if (d[src][vtx] != -1)
			continue;

		d[src][vtx] = dst;
		for (auto x : adj[vtx])
			if (d[src][x.fst] == -1)
				pq.push({dst + x.snd, x.fst});
	}	
}

ll tot;

bool test(ll val){
	init();
	int src, snk;
	src = 0;
	snk = n + 200;

	frr(i, n) // começa em 1 até n
		if (p[i] > 0)
			add(src, i, p[i]);
	frr(i, s) // começa em n + 1 até n + 10
		add(n + i, snk, c[i]);

	frr(i, s){
		frr(j, n)
			if (d[i][j] <= val and d[i][j] != -1)
				add(j, n + i, llINF);
	}	
			
	return dinic(src, snk) >= tot;
}

int32_t main(){
	fastio;
	cin>>n>>m>>s;

	frr(i, n){
		cin>>p[i];
		tot += p[i];
	}

	ll u, v, w;	
	fr(i, m){
		cin>>u>>v>>w;
		adj[u].pb({v, w});
		adj[v].pb({u, w});
	}

	frr(i, s)
		cin>>l[i]>>c[i];

	frr(i, s)
		dij(i);

	ll ini, fim, meio, best;
	ini = 0;
	fim = best = 2e14;

	while (ini <= fim){
		meio = (ini + fim)/2;
		if (test(meio)){
			best = meio;
			fim = meio - 1;
		}
		else
			ini = meio + 1;
	}

	cout<<best<<endl;			
}