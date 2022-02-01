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
const ll mod = 1e9+7;

const int MAXN = 1e5 + 10;

int n, m, dist[MAXN];
vi adj[MAXN];

void bfs(){
	fill(dist, dist + n + 10, -1);
	
	queue<int> fila;
	fila.push(1);
	dist[1] = 0;

	int aux;
	while (!fila.empty()){
		aux = fila.front();
		fila.pop();
		for (int x : adj[aux]){
			if (dist[x] == -1){
				dist[x] = dist[aux] + 1;
				fila.push(x);
			}
		}
	}
}

int32_t main(){
	fastio;
	cin>>n>>m;

	int a, b;
	fr(i, m){
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	bfs();

	cout<<dist[n] - 1<<endl;
}