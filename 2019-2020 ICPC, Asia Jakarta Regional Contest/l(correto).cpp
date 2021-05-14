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

const int MAXN = 2e4 + 3000;
const int MAXM = 9e5;
using namespace std;

int ned, first[MAXN], work[MAXN], dist[MAXN], q[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM];
vi radj[MAXN];



void init(){
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, int f){
	to[ned] = v, cap[ned] = f;
	nxt[ned] = first[u];
	first[u] = ned++;
	
	radj[v].pb(ned); 
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

// COLOCA VERTICES EM U

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
int k, m,  c[MAXN], a[MAXN], nmat[MAXN], freq[MAXN];
int ansa[MAXN], ansb[MAXN];

bool in_cicle[MAXN];

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
		freq[c[i]]++;
		rwrk[c[i]].pb(i);
	}

	frr(i, m)
		fr(j, nmat[i]){
			// cout<<i<<' '<<j<<' '<<mat[i][j]<<' '<<cmp[mat[i][j]]<<endl;
			mat[i][j] = cmp[mat[i][j]];	
		}

	cicledetec(1, 1); // acha o circuito

	bool passei = 0;
	vi cicle;
	for (int u : stk){
	    if (u == batata)
	        passei = 1;
		if (passei){
			in_cicle[u] = 1;
			cicle.pb(u);
		}
    }

    init();
    int src = 0;
    int mid = m + cnt + 10;
    int snk = mid + 1;

    // dbg(cicle.size());
    add(src, mid, (int)(cicle.size()) - 1); // no máximo |C| - 1 arestas

    for (int i = 1; i <= m; i++)
    	if (in_cicle[i] == 0)
    		add(src, i, 1);
    	else
    		add(mid, i, 1);

    for (int i = 1; i <= m; i++)
    	for (int j : mat[i])
    		add(i, j + m, 1); //arestas importantes

    for (int i = 1; i < cnt; i++)
    	add(i + m, snk, freq[i]);

    if (dinic(src, snk) < m - 1){
    	cout<<-1<<endl;
    	return 0;
    }
    		
    for (int i = 1; i < cnt; i++)
    	for (auto e : radj[i + m])
    		if (cap[e] != 0){ // passou fluxo
    			int u = rwrk[i].back();
    			rwrk[i].pop_back();
    			ansa[u] = to[e];
    			ansb[u] = a[to[e]];
    		}
    frr(i, k)
    	cout<<ansa[i]<<" "<<ansb[i]<<endl;   
}