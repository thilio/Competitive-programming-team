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
const int MAXN = 5e5 + 10;

ll n, m;
ll t[2 * MAXN];

void modify(int p, int value) {  
  for (t[p += n] += value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

ll query(int l, int r) {  // sum on interval [l, r)
  ll res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}

int sz[MAXN], dep[MAXN], in[MAXN], out[MAXN], rt[MAXN], clk;
vi adj[MAXN];

void dfs_sz(int v, int p = -1){
	sz[v] = 1;
	in[v] = clk;
	rt[clk++] = v;
	for (auto &x : adj[v]){
		if (x != p){
			dep[x] = dep[v] + 1;
			dfs_sz(x, v);
			sz[v] += sz[x];
			if (sz[x] > sz[adj[v][0]] or adj[v][0] == p) // adj[v][0] é sempre o filho pesado
				swap(x, adj[v][0]);
		}
	}
	out[v] = clk - 1;
}

ll dfs(int v, int p, int val, bool keep = 0){
	int bc = adj[v].size() > 1 ? adj[v][0] : -1;
	
	ll ans = 0;

	for (int u : adj[v]){
		if (u != p and u != bc)
			ans += dfs(u, v, val);
	}

	if (bc != -1)
		ans += dfs(bc, v, val, 1);

	for (auto u : adj[v])
		if (u != p and u != bc){
	    	for(int x = in[u]; x <= out[u]; x++){
				int k = rt[x];
				if (val + (2 * dep[v]) - dep[k] > 0)
					ans += query(0, val + (2 * dep[v]) - dep[k] + 1);
	    	}
	    	for(int x = in[u]; x <= out[u]; x++){
				int k = rt[x];
				modify(dep[k], 1);
	    	}
	    }

	ans += query(0, val + dep[v] + 1);    
	modify(dep[v], 1);

    if (!keep){
     	for(int x = in[v]; x <= out[v]; x++){
     		int k = rt[x];
			modify(dep[k], -1); // diminui uma cor nessa freq
    	}
    }

    return ans;
}

void solve(){
	int l, r;
	cin>>n>>l>>r;

	fr(i, n + 10)
		adj[i].clear();

	int x, y;
	fr(i, n - 1){
		cin>>x>>y;
		adj[x].pb(y);
		adj[y].pb(x);
	}

	dep[1] = clk = 0;
	dfs_sz(1);
	memset(t, 0, sizeof t);
	ll ans = dfs(1, 1, n - l - 1, 0);
	ans -= dfs(1, 1, n - r - 2, 0);

	cout<<ans<<endl;
}


int32_t main(){
	fastio;
	freopen("awesome.in", "r", stdin);
	int T;
	cin>>T;
	while (T--)
		solve();
}