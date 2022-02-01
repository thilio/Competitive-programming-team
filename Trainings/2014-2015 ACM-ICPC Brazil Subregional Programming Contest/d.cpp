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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int n, m;
vii adj[MAXN];

int dist[MAXN];
void dij(int src){
	memset(dist, -1, sizeof dist);
	priority_queue<pii, vector<pii>, greater<pii> > pq;
	pq.push({0, src});

	int dst, vtx;
	while (!pq.empty()){
		tie(dst, vtx) = pq.top();
		pq.pop();

		if (dist[vtx] != -1)
			continue;
		dist[vtx] = dst;

		for (auto x : adj[vtx])
			if (dist[x.fst] == -1)
				pq.push({dst + x.snd, x.fst});
	}
}

int pai[MAXN], cpai[MAXN], hgt[MAXN];
int vis[MAXN];
void dfs(int v){
	vis[v] = 1;
	for (auto x : adj[v])
		if (!vis[x.fst]){
			pai[x.fst] = v;
			cpai[x.fst] = x.snd;
			hgt[x.fst] = hgt[v] + 1;
			dfs(x.fst);
		}
}

vi stk;

int mark(int u, int v){
	int cost = 0;
	if (hgt[u] < hgt[v])
		swap(u, v);
	while (hgt[u] > hgt[v]){
		stk.pb(u);
		cost += cpai[u];
		u = pai[u];
	}
	stk.pb(u);

	if (u == v)
		return cost;

	while (pai[u] != pai[v]){
		stk.pb(u);
		stk.pb(v);
		cost += cpai[u] + cpai[v];
		u = pai[u];
		v = pai[v];
	}
	stk.pb(pai[u]);

	return cost + cpai[u];
}

int cicle[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>m;

	int a, b, c;
	fr(i, m){
		cin>>a>>b>>c;
		adj[a].pb({b, c});
		adj[b].pb({a, c});
	}

	for (int i = 1; i <= n; i++){
		if (!vis[i]){
			dfs(i);
			pai[i] = i;
			cpai[i] = 0;
		}	
	}

	memset(cicle, INF, sizeof cicle);

	for (int v = 1; v <= n; v++)
		for (auto x : adj[v]){
			int u = x.fst;
			if (u != pai[v] and v != pai[u] and cicle[u] == INF){
				stk.clear();
				c = mark(u, v) + x.snd;
				while (!stk.empty()){
					cicle[stk.back()] = c;
					stk.pop_back();
				}
			}
	}

	int q;
	
	cin>>q;
	while (q--){
		cin>>a>>b;
		dij(a);
		int ans = INF;
		for (int v = 1; v <= n; v++){
			if (cicle[v] >= b)
				ans = min(ans, 2 * dist[v] + cicle[v]);
		}

		if (ans == INF)
			cout<<-1<<endl;
		else
			cout<<ans<<endl;
	}
}