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
const int MAXN = 1e5 + 10;

int n, ans[MAXN];
vi adj[MAXN];

void dfs(int v, int p){
	ans[v] = 0;
	if (adj[v].size() == 1 and v != 1){
		ans[v] = 1;
		return;
	}

	for (auto u : adj[v])
		if (u != p){
			dfs(u, v);
			ans[v] += ans[u];
		}

	if (ans[v] == 0)
		ans[v] = 1;
	else
		ans[v]--;
}	


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n;

	int a, b;
	fr(i, n - 1){
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	dfs(1, 1);

	cout<<(ans[1] == 0 ? "Bob" : "Alice")<<endl;
}