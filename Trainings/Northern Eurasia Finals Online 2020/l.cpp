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
const int MAXN = 2e5 + 10;

int n, key[MAXN], lft[MAXN], rgt[MAXN];
vii nodes;

vi adj[MAXN];
int pos[MAXN], sz[MAXN], pai[MAXN], h[MAXN], hgt[MAXN], clk;

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
	for (auto &x : adj[v])
		if (x != p){
			pai[x] = v;
			hgt[x] = hgt[v] + 1;
			if (x == adj[v][0])
				h[x] = h[v]; // na mesma cadeia que o pai
			else
				h[x] = x; // nova cabeça de cadeia
			dfs_build(x, v);
		}
}

void build(int r){ // monta a hld com raiz r
	clk = 0;
	hgt[r] = 0;
	h[r] = r;
	dfs_sz(r);
	dfs_build(r);
}

int lca(int a, int b){ // lca de a e b
	if (pos[a] < pos[b])
		swap(a, b);
	return h[a] == h[b] ? b : lca(pai[h[a]], b);
}

bool anc(int a, int b){ // a é ancestral de b?
	return pos[a] <= pos[b] and pos[b] <= pos[a] + sz[a];
}

int tolft[MAXN], torgt[MAXN];


int getl(int val){
	auto it = lower_bound(all(nodes), make_pair(val, -1));

	int v = (*it).snd;

	if (lft[v] != 0)
		return lft[v];

	return torgt[v];
}

int getr(int val){
	auto it = upper_bound(all(nodes), make_pair(val, INF)) - 1;

	int v = (*it).snd;

	if (rgt[v] != 0)
		return rgt[v];
	return tolft[v];	
}


void prep(int v, int p, int f){
	if (f == 0){ // filho esquedo
		torgt[v] = torgt[p];
		tolft[v] = v;
	}	
	else{
		torgt[v] = v;
		tolft[v] = tolft[p];
	}

	if (lft[v] != 0)
		prep(lft[v], v, 0);
	if (rgt[v] != 0)
		prep(rgt[v], v, 1);
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n;

	frr(i, n){
		cin>>lft[i]>>rgt[i]>>key[i];
		nodes.pb({key[i], i});

		if (lft[i] != 0)
			adj[i].pb(lft[i]);
		if (rgt[i] != 0)
			adj[i].pb(rgt[i]);
	}

	tolft[1] = torgt[1] = 1;
	prep(1, 1, 0);

	build(1);

	sort(all(nodes));

	int q, l, r;

	cin>>q;
	while (q--){
		cin>>l>>r;

		if (l > nodes[n - 1].fst or r < nodes[0].fst){
			cout<<1<<endl;
			continue;
		}

		if (l <= nodes[0].fst and nodes[n - 1].fst <= r){ // only root
			cout<<1<<endl;
			continue;
		}	


		int vl = getl(l);
		int vr = getr(r);

		if (hgt[vl] < hgt[vr])
			swap(vl, vr);

		if (anc(vr, vl)){
			cout<<2 * hgt[vl] + 1<<endl;
			continue;
		}

		int w = lca(vl, vr);

		cout<<2 * (hgt[vl] + hgt[vr] - hgt[w]) - 1<<endl;
	}
}