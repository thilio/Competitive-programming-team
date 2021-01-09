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
const int MAXN = 3000;
const int MAXM = 3e5;

int ned, first[MAXN], work[MAXN], dist[MAXN], q[MAXN];
int cap[MAXM], to[MAXM], from[MAXM], nxt[MAXM];

void init(){
	memset(first, -1, sizeof first);
	ned = 0;
}

void add(int u, int v, int f){
	to[ned] = v, from[ned] = u, cap[ned] = f;
	nxt[ned] = first[u];
	first[u] = ned++;
	
	to[ned] = u, from[ned] = v, cap[ned] = 0;
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

int snk, src, in[MAXN];
vii ans;
stack<pii> stk, path;

int vtx;
bool vis[MAXN];

bool dfs2(int v){
	vis[v] = 1;
	
	if (v == snk){ // cuidado com a ordem das trocas
		path.pop();
		while (!path.empty()){
			while (!in[path.top().fst]){// não trocar dois caras do mesmo time, um sai
				stk.push(path.top());
				path.pop();
			}
			stk.push(path.top());
			path.pop();	
			while (!stk.empty()){//fazer ao contrádio, mantém o meio, troca as pontas
				ans.pb(stk.top());
				stk.pop();
			}
		}		
		return true;
	}

	for (int e = first[v]; e != -1; e = nxt[e])
		if (!(e&1) and cap[e^1] > 0 and !vis[to[e]]){
			path.push({v, to[e]});
			if (dfs2(to[e])){
				if (to[e] == snk)
					vtx = v;
				cap[e^1]--;
				return true;
			}
			path.pop();
		}

	return false;
}

int32_t main(){
	fastio;
	init();

	int n, k;
	cin>>n>>k;

	src = 0;
	snk = n + 1;

	int x;
	fr(i, k){
		cin>>x;
		in[x] = 1;
		add(src, x, 1);
	}

	fr(i, k){
		cin>>x;
		add(x, snk, 1);
	}

	string s;
	frr(i, n){
		cin>>s;
		fr(j, n)
			if (s[j] == '1')
				add(i, j + 1, INF); // não limitar trocas internas
	}

	if (dinic(src, snk) != k){
		cout<<"NO"<<endl;
		return 0;
	}

	cout<<"YES"<<endl;
	
	while (k > 0){
		memset(vis, 0, sizeof vis);
		for (int e = first[src]; e != -1; e = nxt[e])
			if (!(e&1) and cap[e^1] > 0 and dfs2(to[e])){ // aresta que foi usada (par/cap rev. positivo)
				in[to[e]] = 0;
				in[vtx] = 1;
				cap[e^1]--;
				k--;
				break;
			}	
	}

	cout<<ans.size()<<endl;
	for (auto x : ans)
		cout<<x.fst<<' '<<x.snd<<endl;	
}