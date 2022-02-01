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
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 5e3 + 10;

int n;
vi adj[MAXN], adjt[MAXN];
int stk[MAXN], st, scc[MAXN];
bool vis[MAXN];


void dfs1(int v){
	vis[v] = 1;
	for (int u : adj[v])
		if (!vis[u])
			dfs1(u);
	stk[st++] = v;	
}

void dfs2(int v, int cmp){
	scc[v] = cmp;
	for (int u : adjt[v])
		if (scc[u] == -1)
			dfs2(u, cmp);
}

bool sat(){
	fill(vis, vis + n + 10, 0);
	fill(scc, scc + n + 10, -1);
	st = 0;

	for (int i = 2; i <= n; i++)
		if (!vis[i])
			dfs1(i);

	int v, cmp = 0;	
	while (st > 0){
		v = stk[--st];
		if (scc[v] == -1)
			dfs2(v, cmp++);
	}

	for (int i = 2; i <= n; i += 2){
		if (scc[i] == scc[i + 1])
			return false;
	}	
	return true;			
}

void add(int a, int b){
	adj[a].pb(b);
	adjt[b].pb(a);
}

void remove(int a, int b){
	adj[a].pop_back();
	adjt[b].pop_back();
}

int32_t main(){
	fastio;
	int m;
	cin>>n>>m;

	bool ok = 0;
	int a, b;

	fr(i, m){ //2k (true) e 2k + 1(false)
		cin>>a>>b;
		if (a < 0 and b < 0)
			ok = 1;

		if (a > 0 and b > 0){
			add(2 * a + 1, 2 * b);
			add(2 * b + 1, 2 * a);
		}
		else if (a < 0 and b > 0){
			a = -a;
			add(2 * a, 2 * b);
			add(2 * b + 1, 2 * a + 1);
		}
		else if (a > 0 and b < 0){
			b = -b;
			add(2 * b, 2 * a);
			add(2 * a + 1, 2 * b + 1);
		}
		else{
			a = -a;
			b = -b;
			add(2 * a, 2 * b + 1);
			add(2 * b, 2 * a + 1);
		}
	}

	if (ok == 0){
		cout<<-1<<endl;
		return 0;
	}

	n = 2 * n + 1;
	if (!sat()){
		cout<<0<<endl;
		return 0;
	}

	frr(i, (n - 1)/2){
		add(2 * i + 1, 2 * i);
		if (!sat()){
			cout<<1<<endl;
			return 0;
		}
		remove(2 * i + 1, 2 * i);
	}

	cout<<2<<endl;
}