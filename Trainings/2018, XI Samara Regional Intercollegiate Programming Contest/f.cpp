#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

//#define endl '\n'
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
const int MAXN = 1e3 + 10;

int n, pai[MAXN];
vi suc[MAXN], ant[MAXN], adj[MAXN];

bool chk[MAXN];
bool check(int v, int u){
	memset(chk, 0, sizeof chk);
	for (int x : ant[u])
		chk[x] = 1;
	chk[v] = 0;
	for (int x : ant[v])
		if (chk[x] == 0)
			return false;
		else
			chk[x] = 0;
	return true;	
}

int nnode;
bool vis[MAXN];
bool dfs(int v){
	vis[v] = 1;
	nnode++;
	for (int x : suc[v]){
		if (ant[x].size() == ant[v].size() + 1){ // filho
			if (vis[x])
				return false;
			if (!check(v, x))
				return false;
			pai[x] = v;
			dfs(x);
		}
	}
	return true;
}

int32_t main(){
	fastio;

	cin>>n;

	int k, x;
	frr(i, n){
		cin>>k;
		fr(j, k){
			cin>>x;
			suc[i].pb(x);
			ant[x].pb(i);
		}
	}

	memset(pai, -1, sizeof pai);

	int r = -1;
	for (int v = 1; v <= n; v++)
		if (ant[v].empty())
			r = v;
	if (r != -1)
		pai[r] = r;	
	else{
		cout<<"NO"<<endl;
		return 0;
	}

	if(!dfs(r) or nnode != n)
		cout<<"NO"<<endl;
	else{
		cout<<"YES"<<endl;
		for (int v = 1; v <= n; v++)
			if (pai[v] != v)
				cout<<pai[v]<<' '<<v<<endl;
	}
}