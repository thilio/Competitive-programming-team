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

int n, m, k;
vi g[MAXN];

int to_state(int msk){
	int ans = 0;

	fr(i, n)
		if (msk&(1<<i)){ // esse nó está ligado
			for (auto j : g[i]) // o vizinho estará
				ans |= (1<<j);
		}

	return ans;
}


vi adj[MAXN];
vii radj[MAXN];


string bit_to_string(int msk){
	string s;
	fr(i, n)
		if (msk & (1<<i))
			s.pb('a' + i);
	return s;	
}

string move(int v, int u){
	for (auto x : radj[v])
		if (x.fst == u)
			return bit_to_string(x.snd);
		
	return "fudeu";	
}


int dist[MAXN], pai[MAXN], to[MAXN];


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>m>>k;

	fr(i, m){
		int u, v;
		cin>>u>>v;
		u--;
		v--;
		g[u].pb(v);
		g[v].pb(u);
	}

	// li o grafo

	for (int msk = 1; msk < 1<<n; msk++)
		to[msk] = to_state(msk); // quando a contaminação propagar nessa mask, pra que estado vou?
	// calculei a transformação do virus

	for (int msk = 1; msk < (1 << n); msk++) // todos os estados
		for (int smsk = (msk - 1) & msk; smsk > 0; smsk = (smsk - 1) & msk) // percorre todas subamsks
			if (__builtin_popcount(smsk) <= k){// estou desligando k
 				int u = to[msk ^ smsk]; // desliguei a smsk
 				adj[u].pb(msk); // faz adj ao contrario, vou partir do estado final
 				radj[msk].pb({u, smsk});
 			}
 		
 	// montei o grafo
 	
 	memset(dist, -1, sizeof dist);
 	queue<int> fila;

	for (int msk = 1; msk < (1 << n); msk++)
		if (__builtin_popcount(msk) <= k){ // posso eliminar esse estado
			fila.push(msk);
			dist[msk] = 0;
			pai[msk] = msk;
		}	


	while (!fila.empty()){
		int u = fila.front();
		fila.pop();

		for (auto x : adj[u]) // esse cara chega em mim com 1 movimento
			if (dist[x] == -1){
				dist[x] = dist[u] + 1;
				pai[x] = u;
				fila.push(x);
			}	
	}

	int v = (1<<n) - 1;

	if (dist[v] == -1){
		cout<<-1<<endl;
		return 0;
	}

	cout<<dist[v] + 1<<endl;
	while (v != pai[v]){
		cout<<move(v, pai[v])<<endl;
		v = pai[v];
	}
	cout<<bit_to_string(v)<<endl; // me eliminar
}