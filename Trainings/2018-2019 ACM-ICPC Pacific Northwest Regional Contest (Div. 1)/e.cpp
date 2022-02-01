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
const ll mod = 1e9 + 7;

const int MAXN = 1e5 + 3000;
const int MAXM = 9e5;

ll ned, first[MAXN], work[MAXN], dist[MAXN], q[MAXN];
ll cap[MAXM], to[MAXM], nxt[MAXM];

void init() {
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(ll u, ll v, ll f) {
	to[ned] = v, cap[ned] = f;
	nxt[ned] = first[u];
	first[u] = ned++;
	
	to[ned] = u, cap[ned] = 0;
	nxt[ned] = first[v];
	first[v] = ned++;
}

ll dfs(ll u, ll f, ll t) {
	if (u == t) return f;
	for(ll &e = work[u]; e != -1; e = nxt[e]) {
		ll v = to[e];
		if (dist[v] == dist[u] + 1 && cap[e] > 0) {
			ll df = dfs(v, min(f, cap[e]), t);
			if (df > 0) {
				cap[e] -= df;
				cap[e^1] += df;
				return df;
			}
		}
	}
	return 0;
}

bool bfs(ll s, ll t) {
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	ll st = 0, en = 0;
	q[en++] = s;
	while (en > st) {
		ll u = q[st++];
		for(ll e = first[u]; e!=-1; e = nxt[e]) {
			ll v = to[e];
			if (dist[v] < 0 && cap[e] > 0) {
				dist[v] = dist[u] + 1;
				q[en++] = v;
			}
		}
	}
	return dist[t] >= 0;
}

ll dinic(ll s, ll t) {
	ll flow = 0, f;
	while (bfs(s, t)) {
		memcpy(work, first, sizeof work);
		while (f = dfs(s, INF, t)) 
			flow += f;
	}
	return flow;
}

int mx[4] = {1, -1, 0, 0};
int my[4] = {0, 0, 1, -1};

int n, m, c, cst[400];
char mapa[33][33];

int crd(int x, int y){ return x * n + y;}

bool valid(int x, int y){
	if (x < 0 or y < 0)
		return false;
	if (x >= n or y >= m)
		return false;
	return true;
}


int32_t main(){
	fastio;
	init();

	cin>>m>>n>>c;

	int src, snk;
	snk = 2 * n * m + 1;

	string s;
	fr(i, n){
		cin>>s;
		fr(j, m){
			mapa[i][j] = s[j];
			if (mapa[i][j] == 'B')
				src = crd(i, j);
		}
	}

	fr(i, c)
		cin>>cst[i + 'a'];
	cst['.'] = cst['B'] = INF;

	// Dentro das celulas
	fr(i, n)
		fr(j, m)
			add(crd(i, j), crd(i, j) + n * m, cst[mapa[i][j]]);

	// Entre as celulas		
	int x, y;		
	fr(i, n){
		fr(j, m){
			fr(k, 4){
				x = i + mx[k];
				y = j + my[k];
				if (valid(x, y))
					add(crd(i, j) + n * m, crd(x, y), INF);
				else
					add(crd(i, j) + n * m, snk, INF);
			}
		}	
	}

	ll flow = dinic(src, snk);
	if (flow >= INF)
		cout<<-1<<endl;
	else
		cout<<flow<<endl;
}