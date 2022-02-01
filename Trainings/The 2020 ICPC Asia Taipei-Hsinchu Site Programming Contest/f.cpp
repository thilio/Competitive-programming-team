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

int n, m;
vi adj[200200];

int dfs_m[200200][2];

int pd[200200][2][2];

int mn[200200];
int mx[200200];

int dfs(int v, int p, bool must){
	if(dfs_m[v][must] != -1) return dfs_m[v][must];
	int &pdm = dfs_m[v][must];

	int tent = 1;
	for(auto x: adj[v]){
		if(x < n || x == p) continue;
		tent += dfs(x, v, 0);
	}
	pdm = tent;

	if(!must){
		tent = 0;
		for(auto x: adj[v]){
			if(x < n || x == p) continue;
			tent += dfs(x, v, 1);
		}
		pdm = min(pdm, tent);
	}

	return pdm;
}

int dp(int ind, bool last, bool first){
	if(ind == n - 1){
		if(first && last){
			return mn[ind];
		}
		else
			return mx[ind];
	}

	int& pdm = pd[ind][last][first];
	if(pdm != -1) return pdm;


	pdm = mx[ind] + dp(ind + 1, 1, first);

	if(last){
		pdm = min(pdm, mn[ind] + dp(ind  + 1, 0, first));
	}

	return pdm;
}


int main(){

	fastio;

	cin >> n >> m;

	fr(i, n + m){
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	ms(dfs_m, -1);

	fr(i, n){
		mn[i] = dfs(i, -1, 0);
		mx[i] = dfs(i, -1, 1);
		//dbg(mn[i]);
		//dbg(mx[i]);
	}

	ms(pd, -1);

	int x = mx[0] + dp(1, 1, 1);
	int y = mn[0] + dp(1, 0, 0);
	//dbg(y);

	cout << min(x, y) << endl;
	



}
