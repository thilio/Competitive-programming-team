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

const int MAXN = 1020;

namespace sat{
	int n; // # de vertices
	vector<int> adj[MAXN], adjt[MAXN];
	int stk[MAXN], st, scc[MAXN];
	bool vis[MAXN], val[MAXN]; // val[k] é o valor de k

	void dfs1(int v){
		vis[v] = 1;
		for (int u : adj[v])
			if (!vis[u])
				dfs1(u);
		stk[st++] = v;	
	}

	void dfs2(int v, int cmp){
		scc[v] = cmp;
		for (int u : adjt[v])
			if (scc[u] == -1)
				dfs2(u, cmp);
	}

	bool sat(){
		fill(val, val + n, 0);
		fill(vis, vis + n, 0);
		fill(scc, scc + n, -1);
		st = 0;
		for (int i = 0; i < n; i++)
			if (!vis[i])
				dfs1(i);
		int v, cmp = 0;	
		while (st > 0){
			v = stk[--st];
			if (scc[v] == -1)
				dfs2(v, cmp++);
		}
		for (int i = 0; i < n; i += 2){
			if (scc[i] == scc[i + 1]) // i = true | i + 1 = false
				return false;
			val[i/2] = scc[i] > scc[i + 1]; // scc[!a] < scc[a] => true
		}	
		return true;			
	}

	void init(){ // LIMPE o grafo
		for (int i = 0; i < n; i++)
			adj[i].clear(), adjt[i].clear();
	}

	void add(int a, int b){
		adj[a].push_back(b);
		adjt[b].push_back(a);
	}
}





int ned = 1, adj[MAXN], to[2 * MAXN * MAXN], nxt[2 * MAXN * MAXN];
int n, m, st, en; // n # de vértices, m # de arestas
int match[MAXN], pai[MAXN], base[MAXN], q[MAXN]; // match[i] = v, (i, v) estão emparelahdos (ou -1)
bool inq[MAXN], inb[MAXN];

void init(){ // limpa o grafo
	ned = 1;
	fill(adj, adj + n, 0);
}

void add_edge(int u, int v){ // adicionar aresta uv
	to[ned] = u, nxt[ned] = adj[v], adj[v] = ned++;
	to[ned] = v, nxt[ned] = adj[u], adj[u] = ned++;	
}

int find_lca(int root, int u, int v){
	static bool inp[MAXN];
	memset(inp, 0, sizeof(inp));
	while (1){
		inp[u = base[u]] = true;
		if (u == root) 
			break;
		u = pai[match[u]];
	}
	while (1){
		if (inp[v = base[v]]) 
			return v;
		v = pai[match[v]];
	}
}

void mark_blossom(int lca, int u) {
	while (base[u] != lca){
		int v = match[u];
		inb[base[u]] = inb[base[v]] = true;
		u = pai[v];
		if (base[u] != lca) 
			pai[u] = v;
	}
}

void blossom_contraction(int s, int u, int v) {
	memset(inb, 0, sizeof(inb));
	int lca = find_lca(s, u, v);
	mark_blossom(lca, u);
	mark_blossom(lca, v);
	if (base[u] != lca)
		pai[u] = v;
	if (base[v] != lca)
		pai[v] = u;
	for (int u = 0; u < n; u++)
		if (inb[base[u]]){
			base[u] = lca;
			if (!inq[u])
				inq[q[en++] = u] = true;
		}
}

void augment_path( int t) {
	int x, w;
	do{
		x = pai[t];
		w = match[x];
		match[x] = t;
		match[t] = x;
		t = w;
	} while (t != -1);
}

bool find_augmenting_path(int s){
	memset(inq, 0, sizeof(inq));
	memset(pai, -1, sizeof(pai));
	for (int i = 0; i < n; i++) 
		base[i] = i;
	st = en = 0;
	q[en++] = s;
	inq[s] = true;
	while (st < en){
		int u = q[st++];
		for (int e = adj[u]; e != 0; e = nxt[e]){
			int v = to[e];
			if (base[u] != base[v] && match[u] != v){
				if ((v == s)||(match[v] != -1 && pai[match[v]] != -1))
					blossom_contraction(s, u, v);
				else if (pai[v] == -1) {
					pai[v] = u;
					if (match[v] == -1){
						augment_path(v);
						return true;
					}
					if (!inq[match[v]])
						inq[q[en++] = match[v]] = true;
				}
			}	
		}
	}
	
	return false;
}

int blossom(){
	int matchc = 0;
	memset(match, -1, sizeof(match));
	for (int v = 0; v < n; v++)
		if (match[v] == -1 && find_augmenting_path(v))
			matchc++;
	return matchc; // cardinalidade do emparelhamento
}





vii edges;

void solve(){
	cin>>n>>m;

	init();
	edges.clear();


	if (m == 0){
		cout<<0<<endl<<endl;
		return;
	}


	int u, v;
	fr(i, m){
		cin>>u>>v;
		u--;
		v--;

		edges.pb({u, v});	
		add_edge(u, v);
	}

	int sz = blossom();


	// sera que é minimo?
	// hora do 2sat
	
	for (v = -1; v < n; v++){ // vertice proibido
		sat::n = 2*n; // ja ta dobrado
		sat::init();

		for (auto x : edges){
			if (x.fst == v or x.snd == v)
				continue;

			if (match[x.fst] == x.snd){ // no maximo uma é verdade
				sat::add(2*x.fst, 2*x.snd + 1);
				sat::add(2*x.snd, 2*x.fst + 1);
			}

			// aresta coberta
			sat::add(2*x.fst + 1, 2*x.snd);
			sat::add(2*x.snd + 1, 2*x.fst);
			
		}

		for (int i = 0; i < n; i++)
			if (i != v and match[i] == -1)
				sat::add(2*i, 2*i + 1);
			
		if (sat::sat()){ // deitei
			vi ans;
			if (v != -1)
				ans.pb(v + 1);
			fr(i, n)
				if(sat::val[i] and i != v)
					ans.pb(i + 1);

			assert(ans.size() <= sz + 1);	

			sort(all(ans));	

			cout<<ans.size()<<endl;
			for (auto x : ans)
				cout<<x<<' ';
			gnl;

			return;
		}
	}	

	cout<<"not smol"<<endl;
}


signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin>>T;

	while (T--)
		solve();
}