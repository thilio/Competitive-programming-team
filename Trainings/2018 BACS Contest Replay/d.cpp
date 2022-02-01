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

int n, val[MAXN], mxdpt;
int t[2 * MAXN];

void modify(int p, int value) {  
	for (t[p += n] += value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
}

int query(int l, int r) {  // sum on interval [l, r)
	int res = 0;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = max(res, t[l++]);
		if (r&1) res = max(res, t[--r]);
	}
	return res;
}

int sz[MAXN], hgt[MAXN], in[MAXN], out[MAXN], rt[MAXN], clk;
vi adj[MAXN];
void dfs_sz(int v, int p = -1){
	sz[v] = 1;
	in[v] = clk;
	rt[clk++] = v;
	for (auto &x : adj[v]){
		if (x != p){
			hgt[x] = hgt[v] + 1;
			dfs_sz(x, v);
			sz[v] += sz[x];
			if (sz[x] > sz[adj[v][0]] or adj[v][0] == p)
				swap(x, adj[v][0]);
		}
	}
	out[v] = clk - 1;
}

int ans[MAXN];

void dfs(int v, int p, bool keep = 0){
	int bc = adj[v].size() > 1 ? adj[v][0] : -1;

	for (int u : adj[v])
		if (u != p and u != bc)
			dfs(u, v);

	if (bc != -1)
		dfs(bc, v, 1); 

	for (auto u : adj[v])
		if (u != p and u != bc){
			for (int x = in[u]; x <= out[u]; x++)
				modify(hgt[rt[x]], -val[rt[x]]);		
		}



	modify(hgt[v], -val[v]);
	
	ans[v] = query(0, mxdpt);

	if (!keep){
		for (int x = in[v]; x <= out[v]; x++)
			modify(hgt[rt[x]], val[rt[x]]); // corrige soma
	}	
	
}


void solve(){
	cin>>n;

	frr(i, n){
		adj[i].clear();
		cin>>val[i];
	}

	int x;
	for (int v = 2; v <= n; v++){
		cin>>x;
		adj[x].pb(v);
		adj[v].pb(x);
	}	

	clk = 0;
	hgt[1] = 0;	
	dfs_sz(1);

	mxdpt = 0;
	frr(i, n)
		mxdpt = max(mxdpt, hgt[i]);
	mxdpt++; // query aberta	

	memset(t, 0, sizeof t);

	frr(i, n)
		modify(hgt[i], val[i]);

	dfs(1, 1);

	for (int v = 2; v <= n; v++)
		cout<<ans[v]<<endl;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int T;
	cin>>T;

	while (T--)
		solve();
}