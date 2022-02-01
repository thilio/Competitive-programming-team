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
const int MAXN = 5e2 + 10;

int n, m, adj[MAXN][MAXN], deg[MAXN];

pii maxp[MAXN];

pii getmax(int v){
	pii ans = {-INF, v};

	for (int u = 0; u < n; u++)
		if (adj[u][v] > ans.fst)
			ans = {adj[u][v], u};
	return ans;
}

pii getnext(){
	pii ans = maxp[0];
	for (int v = 1; v < n; v++)
		if (maxp[v].fst > ans.fst)
			ans = maxp[v];
	return ans;	
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>m;

	int a, b;
	fr(i, m){
		cin>>a>>b;
		a--;
		b--;
		adj[a][b] = -INF;
		adj[b][a] = -INF;
		deg[a]++;
		deg[b]++;
	}

	fr(i, n)
		adj[i][i] = -INF;

	fr(i, n)
		fr(j, n)
			adj[i][j] += deg[i] + deg[j];

	fr(i, n)
		maxp[i] = getmax(i);

	int k = 1000;			

	pii aux = getnext();

	while (aux.fst >= 0){
		k = min(k, aux.fst);

		int v = aux.snd;
		int u = maxp[v].snd; // vou subir o grau de u e v
	
		if (u == v)
			break;

		deg[v]++;
		deg[u]++;

		for (int w = 0; w < n; w++){
			adj[v][w]++;
			adj[u][w]++;

			if (maxp[w].fst < adj[v][w])
				maxp[w] = {adj[v][w], v};
		
			if (maxp[w].fst < adj[u][w])
				maxp[w] = {adj[u][w], u};
		}
		for (int w = 0; w < n; w++){
			adj[w][v]++;
			adj[w][u]++;
		}

		adj[v][u] = adj[u][v] = -INF;


		maxp[v] = getmax(v);
		maxp[u] = getmax(u);

		aux = getnext();
	}


	cout<<k<<endl;

}