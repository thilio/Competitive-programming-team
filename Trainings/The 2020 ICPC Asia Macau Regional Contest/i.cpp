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
const int MAXN = 2e4 + 10;

int n, a[MAXN], b[MAXN], xorv[MAXN];
int ans[2 * MAXN];
vi query[MAXN];

int pai[MAXN], sz[MAXN];
vi adj[MAXN];

void dfs_sz(int v){
	sz[v] = 1;
	for (auto &x : adj[v]){
		dfs_sz(x);
		sz[v] += sz[x];
		if (sz[x] > sz[adj[v][0]]) // filho 0 é sempre o mais pesado
			swap(x, adj[v][0]);
	}
}

vector< array<int, 1<<14> > memo;

void dfs(int v){
	int hc = (adj[v].empty() ? -1 : adj[v][0]);

	xorv[v] = xorv[pai[v]] ^ a[v];

	array<int, 1<<14> &pdm = memo.back();

	for (int i = 0; i < 1<<14; i++)
		pdm[i] = min(pdm[i], pdm[i^a[v]] + b[v]);

	for (auto x : query[v])
		ans[x] = pdm[xorv[v]];

	for (auto x : adj[v])
		if (x != hc){
			memo.pb(memo.back()); // copia da dp atual
			dfs(x);
			memo.pop_back(); // erase it
		}

	if (hc != -1)
		dfs(hc);	
}

signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n;

	int r = 0, ed = 1; // root vextex and number of existing nodes

	string s;
	fr(i, n){
		cin>>s;
		if (s == "ADD"){
			cin>>a[ed]>>b[ed];

			adj[r].pb(ed);
			pai[ed] = r;
			query[ed].pb(i);
			r = ed;
			ed++;
		}
		else{
			r = pai[r];
			query[r].pb(i);
		}
	}

	dfs_sz(0); // build hld

	array<int, 1<<14> aux;
	fill(all(aux), INF);
	aux[0] = 0;

	memo.pb(aux);

	dfs(0);

	fr(i, n)
		cout<<ans[i]<<endl;
}