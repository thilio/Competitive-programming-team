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
const int MAXN = 6e5 + 10;


int n, pode[MAXN][3], l[MAXN][3], r[MAXN][3];
vi adj[MAXN];	

int rpai(int v, int p){
	fr(i, adj[v].size())
		if (adj[v][i] == p)
			return i;
}

void dfs(int v, int p){
	int idp = rpai(v, p);
	if (pode[v][idp] != -1) // já calculei
		return;

	int mn, mx;
	mn = n;
	mx = 1;

	for (auto x : adj[v])
		if (x != p){
			mx = max(mx, x); // maior filho 
			mn = min(mn, x); // menor filho
			dfs(x, v); // resolvo para os meus filhos
		}

	if (adj[v].size() == 1){ // folha
		pode[v][idp] = 1;
		l[v][idp] = r[v][idp] = v; // sou maior e menor label
	}

	if (adj[v].size() == 2){ // mn == mx, tanto faz se é maior ou menor
		int fid = rpai(mn, v); // o vetor v é o pai fid do vetor x

		pode[v][idp] = pode[mn][fid];

		if (mn < v and r[mn][fid] > v)
			pode[v][idp] = 0;
		if (mn > v and l[mn][fid] < v)
			pode[v][idp] = 0;

		l[v][idp] = min(l[mn][fid], v);
		r[v][idp] = max(r[mn][fid], v);
	}

	if (adj[v].size() == 3){
		int lid = rpai(mn, v); // pai na esq
		int rid = rpai(mx, v); // pai na dir

		pode[v][idp] = pode[mn][lid] and pode[mx][rid]; // primeiramente, ambos meus filhos devem poder

		if (r[mn][lid] > l[mx][rid]) // maior da esquerda maior que o menor da direita
			pode[v][idp] = 0;

		l[v][idp] = min({v, l[mn][lid], l[mx][rid]});
		r[v][idp] = max({v, r[mn][lid], r[mx][rid]});

		if (mn > v or mx < v) // não respeita rotulo
			pode[v][idp] = 0; 
	}	

}

vi ans;
void tenta(int v){
	if (adj[v].size() == 1){
		int u = adj[v][0];
		int idp = rpai(u, v);

		if (pode[u][idp] > 0){
			if (u > v and l[u][idp] > v)
				ans.pb(v);
			if (u < v and r[u][idp] < v)
				ans.pb(v);
		}
	}
	else{
		int ul = adj[v][0];
		int ur = adj[v][1];
		int idl = rpai(ul, v);
		int idr = rpai(ur, v);

		if (ul > v or ur < v)
			return;
		if (pode[ul][idl] < 1 or pode[ur][idr] < 1)
			return;
		if (r[ul][idl] > l[ur][idr])
			return;
		if (r[ul][idl] > v)
			return;
		if (l[ur][idr] < v)
			return;
		ans.pb(v);
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n;
	
	if (n == 1){
		cout<<1<<endl;
		return 0;
	}

	int a, b;
	fr(i, n - 1){
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	frr(i, n){
		sort(all(adj[i]));
		if (adj[i].size() > 3){
			cout<<-1<<endl;
			return 0;
		}
	}

	memset(pode, -1, sizeof pode);
	
	for (int v = 1; v <= n; v++)
		for (auto x : adj[v])
			dfs(v, x);

	for (int v = 1; v <= n; v++)
		if (adj[v].size() < 3)
			tenta(v);

	if (ans.size() == 0){
		cout<<-1<<endl;
	}	
	else{
		for (auto x : ans)
			cout<<x<<' ';
		gnl;
	}


}