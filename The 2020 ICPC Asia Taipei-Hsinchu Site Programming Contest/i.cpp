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
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int n, m, sn, clk, id;
int pre[MAXN], lo[MAXN], pa[MAXN], stk[MAXN], bcc[MAXN];
vi adj[MAXN];

int nc, nb;

void dfsRbc(int v){
	pre[v] = lo[v] = clk++;
	int chd = 0;
	bool any = false;
	for (auto x : adj[v]){
		if (pre[x] == -1){
			chd++;
			pa[x] = v;
			dfsRbc(x);
			lo[v] = min(lo[v], lo[x]);
			if (lo[x] >= pre[v])
				any = true;
			if (lo[x] > pre[v])
				nb++;
		}
		else if (x != pa[v])
			lo[v] = min(lo[v], pre[x]);
	}
	bool cut = 0;
	if (v == pa[v] and chd >= 2)
		cut = true;
	if (v != pa[v] and any)
		cut = true;
	nc += cut;
}

void findbc(){
	for (int v = 1; v <= n; v++)
		pre[v] = -1;
	clk = 0;
	for (int v = 1; v <= n; v++)
		if (pre[v] == -1) {
			pa[v] = v;
			dfsRbc( v);
		}
}

void dfsRbcc(int v){
	pre[v] = clk++;
	stk[sn++] = v;
	lo[v] = pre[v];
	for (auto x : adj[v]){
		if (pre[x] == -1){ 
			pa[x] = v; 
			dfsRbcc(x); 
			lo[v] = min(lo[v], lo[x]);
		} 
		else if (x != pa[v]) 
			lo[v] = min(lo[v], pre[x]); 
	} 

	if (lo[v] == pre[v]){
		int u;
		do {
			u = stk[--sn];
			bcc[u] = id;
		} while (u != v);
		id++;
	}
}

int ebcc(){
	for (int v = 1; v <= n; v++)
		pre[v] = -1;
	sn = clk = id = 0;
	for (int v = 1; v <= n; v++)
		if (pre[v] == -1){
			pa[v] = v;
			dfsRbcc(v);
		}
	return id;	
}

int sz[MAXN], szc[MAXN];

void solve(){
	cin>>n>>m;

	fr(i, n + 10){
		adj[i].clear();
		sz[i] = 0;
		szc[i] = 0;	
	}
	nb = nc = 0;

	int a, b;
	fr(i, m){
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}	

	findbc();
	ebcc();

	frr(i, n)
		szc[bcc[i]]++;

	int mx = 1; // aresta sozinha

	for (int v = 1; v <= n; v++)
		for (auto x : adj[v])
			if (bcc[v] == bcc[x]){
				sz[bcc[v]]++;
				mx = max(sz[bcc[v]], mx);
			}

	if (mx > 1)		
		mx /= 2;		

	int ncomp = nb;
	fr(i, id)
		if (szc[i] > 1)
			ncomp++;

	int mdc = __gcd(mx, ncomp);
	mx /= mdc;
	ncomp /= mdc;

	cout<<nc<<' '<<nb<<' '<<ncomp<<' '<<mx<<endl;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin>>T;
	while (T--)
		solve();
}