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
const int MAXN = 1e5 + 10;

int n, f, clk;
int sz[MAXN], pos[MAXN], dpt[MAXN], pai[MAXN], h[MAXN], dist[MAXN];
vector<int> adj[MAXN];

namespace seg{
	pii seg[4 * MAXN]; 
	pii delta[4 * MAXN];
  
  void build(){
  	for (int i = 0; i < 4 * MAXN; i++){
    	seg[i] = {1, 0};
      	delta[i] = {-1, 0};
 	   }
 	}
  
	pii combine(pii a, pii b){
		if (a.fst == 0 or b.fst == 0)
		  return {0, -1};
		if (a.snd == b.snd)
		  return a;
		if (a.snd == -1)
		  return b;
		if (b.snd == -1)
		  return a;
		return {0, -1};  
	}
  
	void unlazy(int node, int l, int r){
		if (delta[node].fst == -1)
			return;
		if (l != r){
			delta[node<<1] = delta[node];
			delta[node<<1|1] = delta[node];
		}
    
		seg[node] = delta[node];
		delta[node] = {-1, 0};
	}

	void update(int node, int l, int r, int ul, int ur, int val){
		unlazy(node, l, r);
		if (r < ul or ur < l)
			return;
		if (ul <= l and r <= ur){
			delta[node] = {1, val};
			unlazy(node, l, r);
			return;
		}

		int meio = (l + r)/2;
		update(node<<1, l, meio, ul, ur, val);
		update(node<<1|1, meio + 1, r, ul, ur, val);
		seg[node] = combine(seg[node<<1], seg[node<<1|1]);
	}

	pii query(int node, int l, int r, int ql, int qr){
		unlazy(node, l, r);
		if (r < ql or qr < l)
			return {1, -1};
		if (ql <= l and r <= qr)
			return seg[node];

		int meio = (l + r)/2;
		pii a = query(node<<1, l, meio, ql, qr);
    	pii b = query(node<<1|1, meio + 1, r, ql, qr);
    
		return combine(a, b);
	}
  
  	void pupdate(int a, int b, int x){
		a++; b++;
		update(1, 1, n, a, b, x);
	}

	pii pquery(int a, int b){
		a++; b++;
		return query(1, 1, n, a, b);
	}
};

void dfs_hld(int v, int p = -1){
	sz[v] = 1;
	for (auto &x : adj[v]){
		if (x != p){
			dpt[x] = dpt[v] + 1;
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
	dpt[r] = 0;
	dfs_hld(r);
	build_hld(r);
	seg::build();
}

pii query_path(int a, int b){
	if (pos[a] < pos[b])
		swap(a, b);
	if (h[a] == h[b])
		return seg::pquery(pos[b], pos[a]); //pos[b] + 1
	return seg::combine(seg::pquery(pos[h[a]], pos[a]), query_path(pai[h[a]], b));
}

void update_path(int a, int b, int x){
	if (pos[a] < pos[b])
		swap(a, b);
	if (h[a] == h[b])
		return (void) seg::pupdate(pos[b], pos[a], x); //pos[b] + 1
	seg::pupdate(pos[h[a]], pos[a], x);
	update_path(pai[h[a]], b, x);
}

int lca(int a, int b){
	if (pos[a] < pos[b])
		swap(a, b);
	return h[a] == h[b] ? b : lca(pai[h[a]], b);
}

vector< tuple<int, int, int> > fam;

int32_t main(){
	fastio;
	cin>>n>>f;

	int x, y;
	fr(i, n - 1){
		cin>>x>>y;
		adj[x].pb(y);
		adj[y].pb(x);
	}

	build(1); // monta hld

	fr(i, f){
		cin>>x>>y;
		fam.pb({ dpt[x] + dpt[y] - 2 * dpt[lca(x, y)], x, y});
	}	

	sort(all(fam));
	reverse(all(fam));

	int cnt = 1;
	for (auto a : fam){
		tie(ignore, x, y) = a;

		pii b = query_path(x, y);

		if (b.fst == 1)
			update_path(x, y, cnt++);
		else{
			cout<<"No"<<endl;
			return 0;
		}			
	}
	cout<<"Yes"<<endl;

}