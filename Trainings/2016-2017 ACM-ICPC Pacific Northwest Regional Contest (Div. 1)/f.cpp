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
const int MAXN = 1e5 + 10;

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
	fill(vis, vis + n, 0);
	fill(scc, scc + n, -1);
	st = 0;

	for (int i = 0; i < n; i++)
		if (!vis[i])
			dfs1(i);

	int v, cmp = 0;	
	while (st > 0){
		v = stk[--st];
		if (scc[v] == -1)
			dfs2(v, cmp++);
	}

	for (int i = 0; i < n; i += 2){
		if (scc[i] == scc[i + 1]) // i = true | i + 1 = false
			return false;
	}	

	return true;			
}

void add(int a, int b){
	adj[a].push_back(b);
	adjt[b].push_back(a);
}

int32_t main(){
	fastio;
	int sz, r, l;

	cin>>sz>>r>>l;

	n = 2 * l; // n do 2-sat

	vii v;

	int a, b;

	fr(i, l){
		cin>>a>>b;
		v.pb({a, b});
	}

	for (int i = 0; i < l; i++){
		for (int j = i + 1; j < l; j++){ // 2k = true, 2k + 1 = false
			if (v[i].fst == v[j].fst){ // estão na mesma linha
				if (v[i].snd - r <= v[j].snd and v[j].snd <= v[i].snd + r){//coluna, !i V !j
					add(2 * i, 2 * j + 1);
					add(2 * j, 2 * i + 1);
				}
			}
			else if (v[i].snd == v[j].snd){ // estão na mesma coluna
				if (v[i].fst - r <= v[j].fst and v[j].fst <= v[i].fst + r){
					add(2 * i + 1, 2 * j);
					add(2 * j + 1, 2 * i);
				}
			}
		}
	}
	
	if (sat())
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;		
}