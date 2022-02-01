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
const int MAXN = 30;

int n;
vi adj[MAXN], ans[MAXN];


void build(int v, int idx){
	if (idx >= adj[v].size()) 
		return;

	build(v, idx + 1);	

	int u = adj[v][idx];
	for (auto x : ans[u]){
		ans[v].pb(x);
		build(v, idx + 1);
	}

	reverse(all(ans[u])); // do the reversed process wen called again
}


void dfs(int v){
	ans[v].pb(v); // from all green to root red
	for (auto x : adj[v])
		dfs(x);

	build(v, 0);
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n;

	for (int i = 2; i <= n; i++){
		int v;
		cin>>v;
		adj[v].pb(i);
	}

	dfs(1);

	cout<<(int)(ans[1].size()) - 1<<endl; // all green state
	for (int i = 1; i < ans[1].size(); i++)
		cout<<ans[1][i]<<' ';
	gnl;
}