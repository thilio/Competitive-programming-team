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
const int MAXN = 1e3 + 10;

int n, m, deg[MAXN], val[MAXN];
vii adj[MAXN];

void toposort(){
	queue<int> fila;
	frr(i, n)
		if (deg[i] == 0)
			fila.push(i);
	while (!fila.empty()){
		int v = fila.front();
		fila.pop();
		for (auto x : adj[v]){
			val[x.fst] = max(val[x.fst], val[v] + x.snd);
			if(--deg[x.fst] == 0)
				fila.push(x.fst);
		}
	}
}

int32_t main(){
	fastio;
	cin>>n>>m;

	int a, b, c;
	frr(i, m){
		cin>>a>>b>>c;
		adj[a].pb({b, c});
		deg[b]++;
	}

	toposort();

	int ans = 0;
	frr(i, n)
		ans = max(ans, val[i]);
	cout<<ans<<endl;	
}