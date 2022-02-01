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
const int MAXN = 4e5 + 10;

int n, b;

namespace seg{
	int t[2 * MAXN];

	void modify(int p, int value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] & t[p^1];
	}

	int query(int l, int r) {  // sum on interval [l, r]
		int res = (1<<22) - 1;
		r++;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) res &= t[l++];
			if (r&1) res &= t[--r];
		}
		return res;
	}
}

vi adj[MAXN];

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

		fr(i, MAXN)
			seg::t[i] = 0;
	}

	int combine(int a, int b){
		return a & b;
	}

	int query_path(int a, int b){
		if (pos[a] < pos[b])
			swap(a, b);
		if (h[a] == h[b])
			return seg::query(pos[b], pos[a]);
		return (seg::query(pos[h[a]], pos[a]) & query_path(pai[h[a]], b));
	}

	void update_node(int v, int val){
		seg::modify(pos[v], val);
	}
}	

int vtx = 1, here[MAXN], val[MAXN];
map<int, int> cmp;
vii event, qry;

void add_node(int x, int y){
		if (cmp[x] == 0) cmp[x] = vtx++;
		if (cmp[y] == 0) cmp[y] = vtx++;
		x = cmp[x];
		y = cmp[y];

		here[x] = 1;

		if (x == y)	y = 0; // x é raiz de um subárvore

		adj[x].pb(y);
		adj[y].pb(x);
	
		int k;
		cin>>k;
		fr(i, k){ // mask dos problemas que x resolve
			cin>>y;
			val[x] |= (1<<(y - 1));
		}
		val[x] |= 1<<21; // x está na sala
		event.pb({0, x});// x entrou
}

int32_t main(){
	fastio;
	cin>>n>>b;

	int x, y, k;
	vi root;
	fr(i, n){
		cin>>x>>y;
		add_node(x, y);		
	}

	int q;
	cin>>q;
	int c;
	while (q--){
		cin>>c;
		if (c == 0){
			cin>>x;
			event.pb({1, cmp[x]}); // x saiu
		}
		else if (c == 1){
			cin>>x>>y;
			qry.pb({cmp[x], cmp[y]});
			event.pb({2, qry.size() - 1}); // faz a query x - y
		}
		else{
			cin>>x>>y;
			add_node(x, y);  // x entrou
		}
	}
	// coloca todos os vétices no grafo
	// controla quem está na sala com o bit 21

	n = vtx;

	frr(i, n - 1)
		if (here[i] == 0){ // todo mundo que não entra na sala
			adj[0].pb(i);  // essa etapa é necessária pro grafo ser conexo
			adj[i].pb(0);
		}

	hld::build(0); // monta hld com raiz 0, um vértice fantasma
	// se um aluno não está na sala ou é o zero
	// o bit 21 está desligado

	for (auto e : event){
		tie(x, y) = e;

		if (x == 0){
			hld::update_node(y, val[y]); // insere aluno
		}
		else if (x == 1){
			hld::update_node(y, 0); // retira aluno
		}
		else{
			int ans = hld::query_path(qry[y].fst, qry[y].snd);
			if (ans & (1<<21)) // todos os alunos estão presentes
				cout<<(__builtin_popcount(ans) - 1)<<endl;
			else
				cout<<-1<<endl;
		}
	}
}