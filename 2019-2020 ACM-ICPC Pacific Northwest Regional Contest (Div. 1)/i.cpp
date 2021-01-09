	#include "bits/stdc++.h"
	using namespace std;

	#define pb push_back
	#define fst first
	#define snd second

	#define fr(i,n)     for (int i = 0; i < n; i++)
	#define frr(i,n)    for (int i = 1; i <= n; i++)

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

	#define MAXN 103000
	#define MAXM 900000

	int ned, first[MAXN], work[MAXN], dist[MAXN], q[MAXN];
	int cap[MAXM], to[MAXM], nxt[MAXM];

	void init(){
		memset(first, -1, sizeof first);
		ned = 0;
	}

	void add(int u, int v, int f){
		to[ned] = v; cap[ned] = f;
		nxt[ned] = first[u];
		first[u] = ned++;

		to[ned] = u; cap[ned] = 0;
		nxt[ned] = first[v];
		first[v] = ned++;
	}

	int dfs(int u, int f, int t){
		if (u == t) return f;
		for(int &e = work[u]; e != -1; e = nxt[e]){
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
			for(int e = first[u]; e!=-1; e = nxt[e]){
				int v = to[e];
				if (dist[v] < 0 and cap[e] > 0){
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

	string v[MAXN];
	vi adj[MAXN];
	int m;

	int comp(int a, int b){
		int dif = 0;
		fr(i, m)
			if (v[a][i] != v[b][i])
				dif++;
		return dif;
	}

	int cor[MAXN];

	void dfsc(int v, int c){
		cor[v] = c;
		for (int x : adj[v])
			if (cor[x] == 0)
				dfsc(x, (c == 1? 2 : 1) );	
	}

	int32_t main(){
		fastio;
		int n;
		cin>>n;

		string s;
		frr(i, n){
			cin>>s;
			v[i] = s;
		}

		m = v[1].size();
	  
		init();

		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				if (comp(i, j) == 2){
					adj[i].pb(j);
					adj[j].pb(i);
				}

		frr(i, n)
			if (cor[i] == 0)
				dfsc(i, 1);

		int src, snk;
		src = 0;
		snk = n + 10;

		frr(i, n)
			if (cor[i] == 1)
				add(src, i, 1);
			else
				add(i, snk, 1);

		frr(i, n){
			if (cor[i] == 1)
				for (int x : adj[i])
					add(i, x, 1);
		}



		cout<<n - dinic(src, snk)<<endl;


	}