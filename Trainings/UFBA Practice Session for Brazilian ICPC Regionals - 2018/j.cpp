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


int n, k, stu[MAXN], stv[MAXN];


int idsu[MAXN], szsu[MAXN], ncomp;

int find(int a){
	if (a == idsu[a]) return a;
	return idsu[a] = find(idsu[a]);  
}

void merge(int a, int b){
	a = find(a);
	b = find(b);

	if (a == b) return;

	if (szsu[a] < szsu[b])
		swap(a, b);

	idsu[b] = a;
	szsu[a] += szsu[b];
	ncomp--;
}

int ans[MAXN];
int sz[MAXN], in[MAXN], out[MAXN], rt[MAXN], clk;
vector<int> adj[MAXN]; // adj da árvore

void dfs_sz(int v, int p = -1){
	sz[v] = 1;
	in[v] = clk;
	rt[clk++] = v;
	for (auto &x : adj[v]){
		if (x != p){
			dfs_sz(x, v);
			sz[v] += sz[x];
			if (sz[x] > sz[adj[v][0]] or adj[v][0] == p) // adj[v][0] é sempre o filho pesado
				swap(x, adj[v][0]);
		}
	}
	out[v] = clk - 1; // in[v] - out[v], tempo de todos os descendentes de v
}


void dfs(int v, int p, bool keep = 0){
	int bc = adj[v].size() > 1 ? adj[v][0] : -1; // filho pesado
	
	for (int u : adj[v])
		if (u != p and u != bc)
			dfs(u, v);

	if (bc != -1)
		dfs(bc, v, 1); // guarda resposta do filho pesado

	for (auto u : adj[v])
		if (u != p and u != bc){
	    	for (int x = in[u]; x <= out[u]; x++){
				int vtx = rt[x];
				merge(stu[vtx], stv[vtx]);
	    	}
    }

    merge(stv[v], stu[v]);

	ans[v] = ncomp;    

    if (!keep){ // apaga trabalho do filho leve
     	for(int x = in[v]; x <= out[v]; x++){
			int vtx = rt[x];
			idsu[stu[vtx]] = stu[vtx];
			idsu[stv[vtx]] = stv[vtx];
			szsu[stu[vtx]] = szsu[stv[vtx]] = 1; 
		}	
		ncomp = k;
    }
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>k;

	int x;
	for (int i = 2; i <= n; i++){
		cin>>x;
		adj[x].pb(i);
		adj[i].pb(x);
	}

	frr(i, n)
		cin>>stu[i]>>stv[i];

	fr(i, MAXN){
		idsu[i] = i;
		szsu[i] = 1;
	}	
	ncomp = k;
	
	dfs_sz(1);
	dfs(1, 1);

	frr(i, n)
		cout<<ans[i]<<endl;
}