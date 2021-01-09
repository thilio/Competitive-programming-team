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
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

ll n, c;
ll gold[MAXN];

vii adj[MAXN];

ll dfs(int v, int p){
	ll ans = 0;

	for (auto x : adj[v])
		if (x.fst != p){
			ans += dfs(x.fst, v);
			ans += 2ll * x.snd * ((gold[x.fst] + c - 1)/c);
			gold[v] += gold[x.fst];
		}

	return ans;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>c;

	frr(i, n)
		cin>>gold[i];

	ll x, y, w;	
	frr(i, n - 1){
		cin>>x>>y>>w;
		adj[x].pb({y, w});
		adj[y].pb({x, w});
	}	

	cout<<dfs(1, 1)<<endl;	
}