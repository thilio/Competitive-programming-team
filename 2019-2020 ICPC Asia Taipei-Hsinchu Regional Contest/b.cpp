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

int n, ans[MAXN];
vi adj[MAXN];

pii dfs(int v, int p){
	int uncovered_sons = 0; // filhos descobertos
	bool covered_edge = 0; // se há aresta ligada, eu estou coberto

	for (int x : adj[v])
		if (x != p){
			pii aux = dfs(x, v);
			uncovered_sons += aux.fst;
			covered_edge |= aux.snd;
		}

	// regra 2 age fantasmagoricamente, pense em retorno {0, 0}

	if (uncovered_sons <= 1){
		if (covered_edge) // regra 3 : k - 1 arestas ligadas, ligo a com meu pai
			return {0, uncovered_sons == 0};
		if (p == v) // ultimo vértice do caminho, preciso cubrir
			ans[v] = 1;
		return {1, 0}; // posso postergar a cobertura
	}
	else{ // 2 ou mais filhos descobertos, preciso cobrir agora
		ans[v] = 1;
		return {0, 1};
	}	
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n;

	int x, y;
	fr(i, n - 1){
		cin>>x>>y;
		adj[x].pb(y);
		adj[y].pb(x);
	}

	dfs(1, 1);

	int val = 0;
	frr(i, n)
		val += ans[i];

	cout<<val<<endl;	
}