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
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e6 + 10;

int n, m, clk;
int sz[MAXN], pos[MAXN], pai[MAXN], h[MAXN], dist[MAXN];
vi adj[MAXN];

void dfs_hld(int v, int p = -1){
	sz[v] = 1;
	for (auto &x : adj[v]){
		if (x != p){
			dfs_hld(x, v);
			sz[v] += sz[x];
			if (sz[x] > sz[adj[v][0]] or adj[v][0] == p)
				swap(x, adj[v][0]);
		}
	}
}

void build_hld(int v, int p = -1){
	pos[v] = clk++;
	for (auto &x : adj[v]){
		if (x != p){
			pai[x] = v;
			dist[x] = dist[v] + 1;
			if (x == adj[v][0])
				h[x] = h[v];
			else
				h[x] = x;
			build_hld(x, v);
		}
	}
}

void build(int r = 0){
	clk = 0;
	h[r] = r;
	dist[r] = 0;
	dfs_hld(r);
	build_hld(r);
}

int lca(int a, int b){
	if (pos[a] < pos[b])
		swap(a, b);
	return h[a] == h[b]? b : lca(pai[h[a]], b);
}	

int crd(int x, int y){
	return x * m + y;
}

void add(int a, int b, int c, int d){
	b = (b + 1)/2;
	d = (d + 1)/2;
	a--, b--, c--, d--;

	adj[crd(a, b)].pb(crd(c, d));
	adj[crd(c, d)].pb(crd(a, b));
}

int32_t main(){
	fastio;

	cin>>n>>m;

	string s;
	getline(cin, s); // input
	fr(i, n + 1){
		getline(cin, s);	
		if (i == 0)
			continue;

		for (int j = 1; j < 2 * m + 1; j += 2){
			if (s[j] == ' ')
				add(i, j, i + 1, j);
			if (s[j + 1] == ' ')
				add(i, j, i, j + 2);
		}
	}

	ll ans = 0;
	int q, a, b, lst;

	build();

	cin>>q;

	q--;
	cin>>a>>b;
	lst = crd(a - 1, b - 1);

	while (q--){
		cin>>a>>b;
		a--, b--;
		ans += dist[lst] + dist[crd(a, b)] - 2 * dist[lca(lst, crd(a, b))];
		lst = crd(a, b);
	}

	cout<<ans<<endl;
}