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

vi adj[100100];
vi comp[100100];
vi diam;
int vis[100100];

pii dfs(int v,int p){
	//dbg(v);
	vis[v] = 1;
	pii ans = {v,0};
	for(auto x: adj[v]){
		if(x == p) continue;
		pii aux = dfs(x,v);
		if(aux.snd + 1 > ans.snd){
			ans = aux;
			ans.snd++;
		}
	}

	return ans;
}

int solve(int v){
	//olar;
	pii k = dfs(v,-1);
	//olar;
	pii a = dfs(k.fst,-1);
	return a.snd;
}

int main(){

	fastio;

	int n,m;
	cin >> n >> m;

	fr(i,m){
		int u,v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	fr(i,n){
		if(vis[i] == 0){
			diam.pb(solve(i));
		}
	}



	sort(all(diam));
	reverse(all(diam));

	int ans = diam[0];

	for(int i = 1;i < diam.size(); i++){
		ans = max(ans, (diam[i] + 1)/2 + (ans + 1)/2 + 1);
	}

	cout << ans << endl;



}
