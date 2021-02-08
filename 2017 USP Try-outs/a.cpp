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
const int MAXN = 1e5 + 10;

int n, m, k, color[MAXN];
vi adj[MAXN];

void dfs(int v, int hgt){
	color[v] = (hgt % k) + 1;
	for (auto x : adj[v])
		if (color[x] == 0)
			dfs(x, hgt + 1);
}	


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>n>>m>>k;

	int a, b;
	fr(i, m){
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	frr(i, n)
		if (color[i] == 0)
			dfs(i, 0);

	for (int v = 1; v <= n; v++)
		for (int x : adj[v])
			if (color[v] == color[x]){
				cout<<-1<<endl;
				return 0;
			}

	frr(i, n)
		cout<<color[i]<<endl;			
}