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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int n, h;
vi adj[MAXN], l;

void dfs(int v, int p){
	for (int u : adj[v])
		if (u != p)
			dfs(u, v);
	if (adj[v].size() == 1)
		l.pb(v);	
}

int32_t main(){
	fastio;
	cin>>n>>h;

	int v, u;
	fr(i, n - 1){
		cin>>v>>u;
		adj[u].pb(v);
		adj[v].pb(u);	
	}

	dfs(h, h);

	cout<<(l.size() + 1)/2<<endl;

	fr(i, (l.size() + 1)/2)
		cout<<l[i]<<' '<<l[(i + l.size()/2) % l.size()]<<endl;
}