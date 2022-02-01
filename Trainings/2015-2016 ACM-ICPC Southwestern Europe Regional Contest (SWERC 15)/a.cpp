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
const int MAXN = 5e3 + 10;

int a, b, n, m, vis[MAXN], filho[MAXN], pai[MAXN];
vi adj[MAXN], radj[MAXN];

int dfs(int v){
	vis[v] = 1;
	int ans = 1;

	for (auto x : adj[v]){
		if (!vis[x])
			ans += dfs(x);
	}

	return ans;
}

int rdfs(int v){
	vis[v] = 1;
	int ans = 1;

	for (auto x : radj[v]){
		if (!vis[x])
			ans += rdfs(x);
	}

	return ans;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>a>>b>>n>>m;

	int x, y;
	fr(i, m){
		cin>>x>>y;
		adj[x].pb(y);
		radj[y].pb(x);
	}

	fr(i, n){
		memset(vis, 0, sizeof vis);
		filho[i] = dfs(i);
	}

	fr(i, n){
		memset(vis, 0, sizeof vis);
		pai[i] = rdfs(i);
	}


	int ans = 0;
	fr(i, n)
		if (n - filho[i] < a)
			ans++;
	cout<<ans<<endl;	
	
	ans = 0;
	fr(i, n)
		if (n - filho[i] < b)
			ans++;
	cout<<ans<<endl;	
	
	ans = 0;
	fr(i, n)
		if (pai[i] > b)
			ans++;
		
	cout<<ans<<endl;	
}