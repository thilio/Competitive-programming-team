#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

// Algoritmo de Dinitz
// Caso geral : O(EV^2)
// Matching bip : O(EV^0.5)
// Arestas são guardadas como uma lista ligada
// first[v] é a primeira aresta, percorrer até -1 (v = nxt[v])

#define INF 0x3f3f3f3f
const int MAXN = 1e5 + 3000;
const int MAXM = 9e5;
using namespace std;

int ned, first[MAXN], work[MAXN], dist[MAXN], q[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM];

int n;
vii voto;

void init(){
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, int f){
	to[ned] = v, cap[ned] = f;
	nxt[ned] = first[u];
	first[u] = ned++;
	
	to[ned] = u, cap[ned] = 0;
	nxt[ned] = first[v];
	first[v] = ned++;
}

int dfs(int u, int f, int t){
	if (u == t) return f;
	for (int &e = work[u]; e != -1; e = nxt[e]){
		int v = to[e];
		if (dist[v] == dist[u] + 1 && cap[e] > 0){
			int df = dfs(v, min(f, cap[e]), t);
			if (df > 0){
				cap[e] -= df;
				cap[e^1] += df;
				return df;
			}
		}
	}
	return 0;
}

bool bfs(int s, int t){
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	int st = 0, en = 0;
	q[en++] = s;
	while (en > st){
		int u = q[st++];
		for (int e = first[u]; e != -1; e = nxt[e]){
			int v = to[e];
			if (dist[v] < 0 && cap[e] > 0){
				dist[v] = dist[u] + 1;
				q[en++] = v;
			}
		}
	}
	return dist[t] >= 0;
}

int dinic(int s, int t){
	int flow = 0, f;
	while (bfs(s, t)){
		memcpy(work, first, sizeof work);
		while (f = dfs(s, INF, t)) 
			flow += f;
	}
	return flow;
}


bool tent(int v){
	int source = 2*n + 1;
	int sink = 2*n + 2;

	init();

	int aux = 0;
	frr(i, n){
		if(voto[i].fst == v || voto[i].snd == v) aux++;
	} 

	//dbg(aux);

	frr(i, n){
		if(i == v) continue;

		if(voto[i].fst != v && voto[i].snd != v){
			//dbg(i);
			add(source, i, 1);
			add(i, voto[i].fst + n, 1);
			add(i, voto[i].snd + n, 1);
		}
		if(i == voto[v].fst || i == voto[v].snd){
			add(i + n, sink, aux - 2);
		}
		else{
			add(i + n, sink, aux - 1);
		}
	}

	//dbg(dinic(source, sink));
	return (dinic(source, sink) < n - aux - 1);
}

int main(){

	fastio;

	cin >> n;
	voto.resize(n + 1);

	frr(i, n) cin >> voto[i].fst >> voto[i].snd;

	int ans = 0;
	frr(i, n){
		ans += tent(i);
	}



	cout << ans << endl;

}
