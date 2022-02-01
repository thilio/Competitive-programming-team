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
const int MAXN = 1e5 + 10;

int n, m;
map<pii, int> keep;
vi adj[MAXN], adjr[MAXN];
int tot;

int vis[MAXN];
void dfs(int v){
	vis[v] = 1;
	for (int x : adj[v])
		if (!vis[x]){
			if (keep[{v, x}] == 0)
				tot++;
			keep[{v, x}] = 1;
			dfs(x);
		}
}

void dfsr(int v){
	vis[v] = 1;
	for (int x : adjr[v])
		if (!vis[x]){
			if (keep[{x, v}] == 0)
				tot++;
			keep[{x, v}] = 1;//reverse
			dfsr(x);
		}
}

void solve(){
	tot = 0;
	keep.clear();
	
	cin>>n>>m;
	
	frr(i, n){
		adj[i].clear();
		adjr[i].clear();
	}

	int x, y;
	fr(i, m){
		cin>>x>>y;
		adj[x].pb(y);
		adjr[y].pb(x);
	}

	frr(i, n + 1) vis[i] = 0;
	dfs(1);

	frr(i, n +1) vis[i] = 0;
	dfsr(1);

	frr(v, n)
		for (int x : adj[v]){
			if (keep[{v, x}] == 1)
				continue;
			else if (tot < 2 * n)
				tot++;
			else
				cout<<v<<' '<<x<<endl;
		}
}

int32_t main(){
	fastio;
	int T;
	cin>>T;
	while (T--)
		solve();
}