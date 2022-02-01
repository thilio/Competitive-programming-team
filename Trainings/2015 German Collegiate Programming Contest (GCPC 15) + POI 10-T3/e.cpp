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

int n, m, k, dist[MAXN];
vii adj[MAXN];

void dij(){
	memset(dist, -1, sizeof dist);
	priority_queue<pii, vii, greater<pii>> pq;	

	pq.push({0, 1});

	int dst, vtx;
	while (!pq.empty()){
		tie(dst, vtx) = pq.top();
		pq.pop();

		if (dist[vtx] != -1)
			continue;
		
		dist[vtx] = dst;

		for (auto x : adj[vtx])
			if (dist[x.fst] == -1)
				pq.push({dst + x.snd, x.fst});
	}
}

vi path;

bool vis[10100][10100];

void dfs(int v, int dst){
	if (v != path[dst]){
		cout<<"yes"<<endl;
		exit(0);
	}

	vis[v][dst] = 1;

	for (auto x : adj[v])
		if (dist[v] == dist[x.fst] + x.snd)
			if (!vis[x.fst][dst - 1])
				dfs(x.fst, dst - 1);
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>m>>k;

	int a, b, c;
	fr(i, k){
		cin>>a;
		path.pb(a);
	}

	fr(i, m){
		cin>>a>>b>>c;
		adj[a].pb({b, c});
		adj[b].pb({a, c});
	}

	dij();

	for (int i = 0; i < k - 1; i++){
		int v = path[i];
		int u = path[i + 1];
		int cnt = 0;
		for (auto x : adj[v])
			if (x.fst == u and dist[u] == dist[v] + x.snd)
				cnt++;
		
		if (cnt > 1){ // aresta multipla no caminho minimo
			cout<<"yes"<<endl;
			return 0;
		}	
	}

	dfs(n, k - 1);

	cout<<"no"<<endl;
}