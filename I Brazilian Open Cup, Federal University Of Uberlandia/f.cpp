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
const int MAXN = 2e5 + 10;


int n;
vector<int> adj[MAXN];
vii edge;
map< pair<int, int>, int > cost;

namespace seg{
	int t[2 * MAXN];

	void build() {  // build the tree
		for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
	}

	void modify(int p, int value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
	}

	int query(int l, int r) {  // sum on interval [l, r)
		int res = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) res += t[l++];
			if (r&1) res += t[--r];
		}
		return res;
	}
}

namespace hld{
	int pos[MAXN], sz[MAXN], pai[MAXN], h[MAXN], clk;

	void dfs_sz(int v, int p = -1){
		sz[v] = 1;
		for (auto &x : adj[v]){
			if (x != p){
				dfs_sz(x, v);
				sz[v] += sz[x];
				if (sz[x] > sz[adj[v][0]] or adj[v][0] == p) 
					swap(x, adj[v][0]); // filho mais pesado em adj[v][0]
			}
		}
	}

	void dfs_build(int v, int p = -1){
		pos[v] = clk++; // contém a subárvore de v sequêncialmente
		
		if (p != -1)
			seg::modify(pos[v], cost[{p, v}]);
			//seg::t[pos[v] + n] = cost[{p, v}];// adicionando aresta na seg
		
		for (auto &x : adj[v])
			if (x != p){
				pai[x] = v;
				
				if (x == adj[v][0])
					h[x] = h[v]; // na mesma cadeia que o pai
				else
					h[x] = x; // nova cabeça de cadeia
				dfs_build(x, v);
			}
	}

	void build(int r){ // monta a hld com raiz r
		clk = 0;
		h[r] = r;
		dfs_sz(r);
		dfs_build(r);
		//seg::build();
	}

	int combine(int a, int b){
		return a + b;
	}

	int query_path(int a, int b){
		if (pos[a] < pos[b])
			swap(a, b);
		if (h[a] == h[b])
			return seg::query(pos[b] + 1, pos[a] + 1); // pos[b] + 1
		return combine(seg::query(pos[h[a]], pos[a] + 1) , query_path(pai[h[a]], b));
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin>>n;

	int a, b, c;
	fr(i, n - 1){
		cin>>a>>b>>c;
		adj[a].pb(b);
		adj[b].pb(a);
		cost[{a, b}] = cost[{b, a}] = c;
		edge.pb({a, b});
	}

	hld::build(1);

	int q;
	cin>>q;

	while (q--){
		cin>>c>>a>>b;
		if (c == 1){
			cout<<hld::query_path(a, b)<<endl;
		}
		else{
			int x = 0;
			if (hld::pai[edge[a - 1].fst] == edge[a - 1].snd)
				x = edge[a - 1].fst;
			else
				x = edge[a - 1].snd;
			seg::modify(hld::pos[x], b);
		}
	}
}