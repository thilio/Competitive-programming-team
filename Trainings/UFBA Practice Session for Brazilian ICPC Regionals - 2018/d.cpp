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


int n, clk, sn, id;
int pre[MAXN], lo[MAXN], stk[MAXN], scc[MAXN]; // scc[v] é a componente forte de v
vector<int> adj[MAXN], adjscc[MAXN];

int nv, nu;

void dfsRscc( int v) {
	pre[v] = lo[v] = clk++;
	stk[sn++] = v;
	for (auto x : adj[v]) {
		if (v == nv and x == nu)
			continue;
		if (pre[x] == -1)
			dfsRscc( x);
		lo[v] = min( lo[v], lo[x]);
	}
	if (lo[v] == pre[v]) {
		int u;
		do {
			u = stk[--sn];
			scc[u] = id;
			lo[u] = INF;
		} while (u != v);
		id++;
	}
}

int tarjan() {
	for (int v = 1; v <= n; v++)
		pre[v] = -1;
	clk = sn = id = 0;
	for (int v = 1; v <= n; v++)
		if (pre[v] == -1)
			dfsRscc( v);
	return id > 1;	
}


vii check;
vi adr[MAXN]; 
int vis[MAXN];

void dfs1(int v){
	vis[v] = 1;
	for (int x : adj[v])
		if (!vis[x]){
			check.pb({v, x});
			dfs1(x);
		}
}

void dfs2(int v){
	vis[v] = 1;
	for (int x : adr[v])
		if (!vis[x]){
			check.pb({x, v});
			dfs2(x);
		}
}

map<pii, int> freq, para;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int m;

	cin>>n>>m;
	int a, b;	
	fr(i, m){
		cin>>a>>b;
		adj[a].pb(b);
		adr[b].pb(a);
		para[{a, b}]++;
	}

	memset(vis, 0, sizeof vis);
	dfs1(1);

	memset(vis, 0, sizeof vis);
	dfs2(1);

	vii ans;
	for (auto e : check){ // possíveis candidatas de ponte forte
			nv = e.fst;
			nu = e.snd;
			if (tarjan())
				if (!freq.count(e) and para[e] == 1){
					ans.pb(e);
					freq[e] = 1;
				}
		}

	cout<<ans.size()<<endl;	
	for (auto e : ans)
		cout<<e.fst<<' '<<e.snd<<endl;
}