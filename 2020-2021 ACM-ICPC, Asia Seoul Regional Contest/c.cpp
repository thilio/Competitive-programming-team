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
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

int especial[MAXN];
int pr[MAXN];
vector<int> adj[MAXN];

int ans = 0, n, k;

int dfs(int v){
	pr[v] = 1;
	int ret = especial[v];

	vector<int> filhos;
	for(auto x : adj[v]){
		if(!pr[x]){
			int aux = dfs(x);
			ret += aux;
			filhos.pb(aux);
		}
	}

	if(especial[v]){
		ans++;
		return ret;
	}

	filhos.pb(k - ret);
	sort(filhos.begin(), filhos.end());
	if(filhos.size() >= 2){
		if(filhos[filhos.size() - 1] > 0 && filhos[filhos.size() - 2] > 0){
			ans++;
		}
	}

	return ret;
}

int main(){
	fastio;
	cin >> n >> k;
	fr(i, n-1){
		int u, v, w;
		cin >> u >> v >> w;

		adj[u].pb(v);
		adj[v].pb(u);
	}
	fr(i, k){
		int x;
		cin >> x;
		especial[x] = 1;
	}

	int aux = dfs(1);
	cout << ans << endl;

}
