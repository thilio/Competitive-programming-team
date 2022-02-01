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

const int MAXN = 1e3 + 10;

int n, m, k, s, t;
vii adj[MAXN], edge, trc;

bool vis[MAXN];
void dfs(int v, int idx){
	vis[v] = 1;

	int a, b, c, d;
	a = trc[idx].fst;
	b = trc[idx].snd;

	for (auto x : adj[v]){
		c = edge[x.snd].fst;
		d = edge[x.snd].snd;
		if (!vis[x.fst] and c <= a and b <= d){
			dfs(x.fst, idx);
		}
	}
}

int32_t main(){
	fastio;

	cin>>n>>m>>k;
	cin>>s>>t;

	set<int> q;
	int a, b, c, d;
	for (int i = 0; i < m; i++){
		cin>>a>>b>>c>>d;
		adj[a].pb({b, i});
		edge.pb({c, d});
		q.insert(c);
		q.insert(d);
	}

	int last = *q.begin();

	while (!q.empty()){
		a = *q.begin();
		q.erase(q.begin());

		if (last + 1 <= a - 1)
			trc.pb({last + 1, a - 1});

		trc.pb({a, a});
		last = a;	
	}

	int ans = 0;

	for (int i = 0; i < trc.size(); i++){
		fill(vis, vis + n + 1, 0);

		dfs(s, i);
		if (vis[t])
			ans += trc[i].snd - trc[i].fst + 1;
	}

	cout<<ans<<endl;
}