#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define endl '\n'

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

bool madj[10010][10010];
vi adj[10010];
int vis[10010];
int n,m;
vector<int> help;

void dfs(int v, int pai){
	vis[v] = 1;
	for(auto x : adj[v]){
		if(madj[v][x] == false) continue;
		if(vis[x] == 1) continue;
		dfs(x, v); 
	}

	for(auto x : adj[v]){
		if(madj[v][x] == true && x != pai) help.pb(x);
	}

	int k = help.size();
	
	if(k%2 == 1){
		help.pb(pai);
		k++;
	}

	fr(i,k/2){
		cout << help[2*i] << ' ' << v << ' '<< help[2*i + 1] << endl;
		madj[v][help[2*i]] = madj[help[2*i]][v] = false;
		madj[v][help[2*i + 1]] = madj[help[2*i + 1]][v] = false;
	}

	help.clear();
}

int main(){

	fastio;

	cin >> n >> m;

	fr(i,m){
		int u,v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
		madj[u][v] = madj[v][u] = true; 
	}

	cout << m/2 << endl; 
	dfs(1, -1);

}
