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

int n, root, r[MAXN], t[MAXN];
vi adj[MAXN];


namespace seg{ // estrutura de dados auxiliar
	ll t[3 * MAXN];

	void modify(int p, ll value) {  
		for (t[p += MAXN] += value; p > 1; p >>= 1) 
			t[p>>1] = t[p] + t[p^1];
	}

	ll query(int l, int r) {  // sum on interval [l, r)
		ll res = 0;
		for (l += MAXN, r += MAXN; l < r; l >>= 1, r >>= 1) {
			if (l&1) res += t[l++];
			if (r&1) res += t[--r];
		}
		return res;
	}
}

int sz[MAXN], hgt[MAXN], in[MAXN], out[MAXN], rt[MAXN], clk; 
ll 	ans[MAXN];

void dfs_sz(int v, int p = -1){
	sz[v] = 1;
	in[v] = clk;
	rt[clk++] = v;
	for (auto &x : adj[v]){
		if (x != p){
			hgt[x] = hgt[v] + 1;
			dfs_sz(x, v);
			sz[v] += sz[x];
			if (sz[x] > sz[adj[v][0]] or adj[v][0] == p) // adj[v][0] é sempre o filho pesado
				swap(x, adj[v][0]);
		}
	}
	out[v] = clk - 1; // in[v] - out[v], tempo de todos os descendentes de v
}

void dfs(int v, int p, bool keep = 0){
	int bc = adj[v].size() > 0 ? adj[v][0] : -1; // filho pesado

	for (int u : adj[v])
		if (u != p and u != bc)
			dfs(u, v);

	if (bc != -1)
		dfs(bc, v, 1); // guarda resposta do filho pesado

	for (auto u : adj[v])
		if (u != p and u != bc){
	    	for (int x = in[u]; x <= out[u]; x++){
				seg::modify( r[ rt[x] ] , t[ rt[x] ] );	
	    	}
	    }


	ans[v] = seg::query(0, r[v]); // aberto na direita    
	seg::modify( r[v] , t[v]); // adiciona v

    if (!keep){ // apaga trabalho do filho leve
     	for(int x = in[v]; x <= out[v]; x++)
			seg::modify(r[ rt[x] ], -t[ rt[x] ]); 
	}	
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n;

	int a, b, c;
	frr(i, n){
		cin>>a>>b>>c;
		r[i] = b;
		t[i] = c;

		if (a != -1)
			adj[a].pb(i);
		else
			root = i;
	}


	hgt[root] = clk = 0;
	dfs_sz(root);
	dfs(root, root);

	frr(i, n)
		cout<<ans[i]<<endl;
}