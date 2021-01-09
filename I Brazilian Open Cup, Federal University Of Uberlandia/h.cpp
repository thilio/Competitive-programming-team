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

int n,m;

vi adj[10010];
int vis[2020];
int start,fim;

pii no;

void dfs(int v){
	vis[v] = 1;

	for(auto x : adj[v]){
		if(mp(v,x) == no) continue;
		if(vis[x]) continue;

		dfs(x);
	}
}

int main(){

	fastio;
	cin >> n >> m;

	fr(i,m){
		int a,b;
		cin >> a >> b;
		adj[a].pb(b);
	}

	cin >> start >> fim;

	bool ans = false;
	frr(i,n){
		for(auto x: adj[i]){
			ms(vis,0);
			no = {i,x};
			dfs(start);
			if(vis[fim] == 0) ans = true;
			//if(vis[fim] == -1){dbg(i);dbg(x);}
		}
	}

	cout << ans << endl;

}
