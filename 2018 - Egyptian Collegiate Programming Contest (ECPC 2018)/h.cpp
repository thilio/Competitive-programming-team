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

int n, m, u, l, k;
int dist[MAXN];

vii adj[MAXN];

void bfs(){
	frr(i, n)
		dist[i] = -1;

	queue<int> fila;	
	fila.push(u); // src
	dist[u] = 0;

	int vtx;
	while (!fila.empty()){
		vtx = fila.front();
		fila.pop();

		for (auto x : adj[vtx])
			if (dist[x.fst] == -1){
				dist[x.fst] = dist[vtx] + 1;
				fila.push(x.fst);
			}
	}
}

void solve(){
	cin>>n>>m>>u>>l>>k;

	frr(v, n)
		adj[v].clear();

	int u, v, w;
	fr(i, m){
		cin>>u>>v>>w;
		adj[u].pb({v, w});
		adj[v].pb({u, w});
	}

	bfs();

	int ans = 0;

	frr(v, n)
		if (dist[v] < k)
			for (auto x : adj[v])
				ans = max(ans, x.snd);

	cout<<ans<<endl;
}

int32_t main(){
	freopen("path.in", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin>>T;
	while (T--)
		solve();
}