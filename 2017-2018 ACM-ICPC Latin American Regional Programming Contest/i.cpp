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

typedef tuple<int, int, int> tup;

int n, m;
vii adj[MAXN];
map<pii, int> cost;
vector<tup> edges;

int id[MAXN], sz[MAXN];
void init_dsu(){
	fr(i, MAXN){
		id[i] = i;
		sz[i] = 1;
	}
}

int find(int a){
	if (id[a] == a)
		return a;
	return id[a] = find(id[a]); 
}

int merge(int a, int b){
	a = find(a);
	b = find(b);
	if (a == b)
		return false;
	if (sz[a] < sz[b])
		swap(a, b);
	id[b] = a;
	sz[a] += sz[b];
	return true;
}

int tot;

void kruskal(){
	init_dsu();
	sort(all(edges));

	int a, b, c;
	for (auto e : edges){
		tie(c, a, b) = e;
		if (merge(a, b)){
			tot += c;
			adj[a].pb({b, c});
			adj[b].pb({a, c});
		}
	}
}

namespace seg{
	int t[2 * MAXN];

	void modify(int p, int value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) 
			t[p>>1] = max(t[p], t[p^1]);
	}

	int query(int l, int r) {  // sum on interval [l, r)
		int res = 0;
		r++;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) res = max(t[l++], res);
			if (r&1) res = max(res, t[--r]);
		}
		return res;
	}
}


namespace hld{
	int pos[MAXN], sz[MAXN], pai[MAXN], h[MAXN], clk;

	void dfs_sz(int v, int p = -1){
		sz[v] = 1;
		for (auto &x : adj[v]){
			if (x.fst != p){
				dfs_sz(x.fst, v);
				sz[v] += sz[x.fst];
				if (sz[x.fst] > sz[adj[v][0].fst] or adj[v][0].fst == p) 
					swap(x, adj[v][0]); // filho mais pesado em adj[v][0]
			}
		}
	}

	void dfs_build(int v, int p = -1){
		pos[v] = clk++; // contém a subárvore de v sequêncialmente
		if (p != -1)
			seg::modify(pos[v], cost[{v, p}]);
		for (auto &x : adj[v])
			if (x.fst != p){
				pai[x.fst] = v;
				if (x.fst == adj[v][0].fst)
					h[x.fst] = h[v]; // na mesma cadeia que o pai
				else
					h[x.fst] = x.fst; // nova cabeça de cadeia
				dfs_build(x.fst, v);
			}
	}

	void build(int r){ // monta a hld com raiz r
		clk = 0;
		h[r] = r;
		dfs_sz(r);
		dfs_build(r);
	}

	int combine(int a, int b){
		return max(a, b);
	}

	int query_path(int a, int b){
		if (pos[a] < pos[b])
			swap(a, b);
		if (h[a] == h[b])
			return seg::query(pos[b] + 1, pos[a]);
		return combine(seg::query(pos[h[a]], pos[a]) , query_path(pai[h[a]], b));
	}

	int lca(int a, int b){ // lca de a e b
		if (pos[a] < pos[b])
			swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>n>>m;

	int a, b, c;
	fr(i, m){
		cin>>a>>b>>c;
		cost[{a, b}] = cost[{b, a}] = c;
		edges.pb({c, a, b});
	}

	kruskal();
	hld::build(1);

	int q;
	cin>>q;

	// fr(i, 2 * n)
	// 	dbg(seg::t[i]);

	while (q--){
		cin>>a>>b;
		// dbg(tot);
		// dbg((cost[{a, b}]));
		// dbg(hld::query_path(a, b));
		cout<<tot - hld::query_path(a, b) + cost[{a, b}]<<endl;	
	}
}