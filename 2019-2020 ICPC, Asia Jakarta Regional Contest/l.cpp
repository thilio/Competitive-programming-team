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
const int MAXN = 5e4 + 10;


vi adju[MAXN];
int matchu[MAXN], matchv[MAXN], dist[MAXN], q[MAXN];
int m, n;

bool bfs(){
	int st = 0, en = 0;
	for (int u = 1; u <= m; u++){
		if (matchu[u] == 0){
			dist[u] = 0; 
			q[en++] = u;
		}
		else dist[u] = INF;
	}
	dist[0] = INF;
	while (en > st){
		int u = q[st++];
		if (dist[u] >= dist[0]) 
			continue;
		for (int v : adju[u]){
			if (dist[matchv[v]] == INF){
				dist[matchv[v]] = dist[u] + 1;
				q[en++] = matchv[v];
			}
		}
	}

	return (dist[0] != INF);
}

bool dfs(int u){
	if (u == 0) return true;
	for (int v : adju[u]){
		if (dist[matchv[v]] == dist[u] + 1){
			if (dfs(matchv[v])){
				matchv[v] = u; 
				matchu[u] = v;
				return true;
			}
		}
	}
	dist[u] = INF;
	return false;
}

int hopcroft(){
	int res = 0;
	while (bfs()){
		for (int u = 1; u <= m; u++)
			if (matchu[u] == 0 and dfs(u))
				res++;
	}
	return res;
}

vi adj[MAXN], stk;
int vis[MAXN], batata;

int cicledetec(int v, int p){
	vis[v] = 1; // ativo
    stk.pb(v);
	for (auto x : adj[v])
		if (x != p){
			if (vis[x] == 1){ // detectei circuito
			    batata = x;
				return true;
			}	
			else
				if (cicledetec(x, v) == 1)
					return true;
		}

    stk.pop_back();
	vis[v] = 2; // inativo
	return false;
}

map<int, int> cmp;
vi mat[MAXN], rwrk[MAXN];
int k, c[MAXN], a[MAXN], nmat[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>m>>k;

	if (k < m - 1){
		cout<<"-1"<<endl;
		return 0;
	}

	frr(i, m){
		cin>>a[i];
		adj[i].pb(a[i]);
		adj[a[i]].pb(i);
		cin>>nmat[i];

		int x;
		fr(j, nmat[i]){
			cin>>x;
			mat[i].pb(x);
			cmp[x]; // liga no
		}
	}

	frr(i, k){
		cin>>c[i];
		cmp[c[i]]; // liga no
	}

	int cnt = 1;
	for (auto &it : cmp)
		it.snd = cnt++; // comprime

	frr(i, k){
		c[i] = cmp[c[i]];
		// dbg(c[i]);
		rwrk[c[i]].pb(i);
	}

	frr(i, m)
		fr(j, nmat[i])
			mat[i][j] = cmp[mat[i][j]];

	cicledetec(1, 1); // acha o circuito

	bool passei = 0;
	vi cicle;
	for (int u : stk){
	    if (u == batata)
	        passei = 1;
		if (passei)
			cicle.pb(u);
    }

	// vou constuir o grafo
 	// lado esquerdo = m
	n = k; // lado direito

	frr(i, m){
		for (int j : mat[i])
			for (int u : rwrk[j]) // tabalhadores desse material
				adju[i].pb(u);
	}

	int nmatch = 0;

	memset(matchu, 0, sizeof matchu);
	memset(matchv, 0, sizeof matchv);

	for (int v : cicle){
		adju[v].clear(); // apaga vizinhos
		
		if (matchu[v] != 0){
			matchv[matchu[v]] = 0;
			matchu[v] = 0;
			nmatch--;
		}
		nmatch += hopcroft();

		if (nmatch >= m - 1){ // deu bom
			frr(i, k)
				cout<<matchv[i]<<' '<<a[matchv[i]]<<endl;
			return 0;	
		}

		for (int j : mat[v])
			for (int u : rwrk[j]) // tabalhadores desse material
				adju[v].pb(u);
	}

	cout<<"-1"<<endl;
}