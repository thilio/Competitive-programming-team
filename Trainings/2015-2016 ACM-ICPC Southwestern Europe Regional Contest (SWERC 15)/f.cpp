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
const int MAXN = 1e5 + 3000;
const int MAXM = 9e5;
using namespace std;

int ned, first[MAXN], work[MAXN], dist[MAXN], q[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM];

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

// problema de corte mínimo, cada lado do corte representa uma altura
// se algum baixo mudou para alto, a aresta {low, v} está cruzando o corte
// e estamos pagando B
// Se v é alto e u é baixo e  {u, v} \in E então a aresta {u, v} está cruzando
// o corte, logo, pagamos custo A.
// Com isso, o corte mínimo representa o menor custo possível para tarefa

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, m, a, b;

	cin>>n>>m>>a>>b;

	vector<string> mapa(n);
	string t;
	fr(i, n)
		cin>>mapa[i];

	init();

	int low = n * m;
	int high = n * m + 1;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++){
			int vtx = (mapa[i][j] == '.'? low : high);
			add(vtx, i * m + j, b);
			add(i * m + j, vtx, b); // custo de mudar o tipo
		
			if (i + 1 < n){
				add(i * m + j, (i + 1) * m + j, a); // custo de mudar de altura
				add((i + 1) * m + j, i * m + j, a);
			}
			if (j + 1 < m){
				add(i * m + j, i * m + j + 1, a);
				add(i * m + j + 1, i * m + j, a);
			}
		}

	cout<<dinic(low, high)<<endl;	
}