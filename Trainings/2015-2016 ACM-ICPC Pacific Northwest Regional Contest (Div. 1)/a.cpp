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
const int MAXN = 1e3 + 10;

vector<int> adju[MAXN]; // adj da partição U
int matchu[MAXN], matchv[MAXN]; 
int dist[MAXN], q[MAXN];
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

int hopcroftKarp(){
	memset(&matchu, 0, sizeof matchu);
	memset(&matchv, 0, sizeof matchv);
	int result = 0;
	while (bfs()){
		for (int u = 1; u <= m; u++){
			if (matchu[u] == 0 and dfs(u))
				result++;
		}
	}
	return result;
}

int cst[MAXN][MAXN], co[MAXN][MAXN], p[MAXN];
int s[MAXN], f[MAXN], t[MAXN], adj[MAXN][MAXN]; 

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>m;

	frr(i, n)
		cin>>p[i];

	frr(i, n)
		frr(j, n){
			cin>>cst[i][j];
			co[i][j] = cst[i][j];
		}

	frr(j, n)
		frr(i, n)
			if (i != j)
				cst[i][j] += p[j]; // adiciona custo da inspeção

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cst[i][j] = min(cst[i][j], cst[i][k] + cst[k][j]);

	frr(i, m)
		cin>>s[i]>>f[i]>>t[i];
	
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			if (i != j){ // de i para j
				int aux = t[i] + co[s[i]][f[i]] + p[f[i]] + cst[f[i]][s[j]];
				if (aux <= t[j])
					adj[i][j] = 1;
			}

	// agora é fathobbits
	
	for (int k = 1; k <= m; k++) // fecho transitivo
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				adj[i][k] |= adj[i][k] & adj[k][j];

	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			if (adj[i][j] and i != j)
				adju[i].pb(j);		

	n = m;		
	cout<<(m - hopcroftKarp())<<endl;		

}