#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define frm(i, n) for(int i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));
#define db cout << "Debug" << endl;
#define all(x) begin(x), end(x)
#define dbg(x)  cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define random mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define myrand(a, b) uniform_int_distribution<int>(a, b)(rng)

#define mp make_pair
#define pq priority_queue

#define MAXN 200010
#define MOD 1000000007
#define INF 2000000000000000100

vector<int> adj[MAXN];
int pr[MAXN];
vector<array<int, 3>> e;
int n;
int ini, fim;


bool dfs(int v){
	pr[v] = 1;
	if(v == fim || v == fim + n) return true;
	bool ok = 0;
	for(auto x: adj[v]){
		if(!pr[x]) ok |= dfs(x);
	}
	return ok;
}

bool tenta(int d){
	frr(i, 2*n) adj[i].clear(), pr[i] = 0;
	for(auto x: e){
		if(x[0] <= d){
			adj[x[1]].pb(x[2]);
			adj[x[2]].pb(x[1]);

			adj[x[1] + n].pb(x[2] + n);
			adj[x[2] + n].pb(x[1] + n);
		}
		else{
			adj[x[1]].pb(x[2] + n);
			adj[x[2]].pb(x[1] + n);
			// cout << x[1] << " " << x[2] + n << endl;
			// cout << x[2] << " " << x[1] + n << endl;
				
		}
	}
	return dfs(ini);
}

signed main(){
	fastio;
	int m;
	cin >> n >> m;
	fr(i, m){
		int a, b, w;
		cin >> a >> b >> w;
		e.pb({w, a, b});
	}
	ini = 1, fim = n;
	int l = -1, r = MOD, mid;
	while(l < r - 1){
		mid = (l + r)/2;
		if(tenta(mid)) r = mid;
		else l = mid;
	}
	//dbg(tenta(1));
	if(r == MOD) cout << -1 << endl;
	else cout << r << endl;
}
