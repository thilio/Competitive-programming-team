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
const int MAXN = 3e5 + 10;

int n, m, sz[MAXN], vis[MAXN];
int x[MAXN], y[MAXN], z[MAXN], cnt;
vi adj[MAXN];

void dfs(int v){
	vi filho;

	sz[v] = vis[v] = 1;

	for (auto x : adj[v]){
		if (!vis[x]){
			dfs(x);
			
			if (sz[x] % 2) // filho impar
				filho.pb(x);
			
			sz[v] += sz[x];
		}
	}

	if (filho.size() % 2){ // tenho que parear algum comigo
		x[cnt] = v;
		y[cnt] = filho.back();
		z[cnt++] = -1;
		filho.pop_back();
	}

	while (!filho.empty()){
		x[cnt] = filho.back();
		filho.pop_back();
		y[cnt] = filho.back();
		filho.pop_back();
		z[cnt++] = v;
	}

}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>m;

	int a, b;
	fr(i, m){
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	for (int i = 0; i < 2 * n; i++){
		if (!vis[i]){
			dfs(i);
			if (sz[i] % 2){ // componente impar
				cout<<"IMPOSSIBLE"<<endl;
				return 0;
			}
		}
	}

	cout<<"POSSIBLE"<<endl;
	fr(i, n)
		cout<<x[i]<<' '<<y[i]<<' '<<z[i]<<endl;
}