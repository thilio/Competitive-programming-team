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
const int MAXN = 1e3 + 100;

vi adju[MAXN];
int matchu[MAXN], matchv[MAXN]; 
int dist[MAXN], q[MAXN];
int m, n;

bool bfs(){
	int st = 0, en = 0;
	for (int u = 1; u <= m; u++){
		if (matchu[u] == 0){
			dist[u] = 0; 
			q[en++] = u;
		}
		else dist[u] = INF;
	}
	dist[0] = INF;
	while (en > st){
		int u = q[st++];
		if (dist[u] >= dist[0]) 
			continue;
		for (int v : adju[u]){
			if (dist[matchv[v]] == INF){
				dist[matchv[v]] = dist[u] + 1;
				q[en++] = matchv[v];
			}
		}
	}

	return (dist[0] != INF);
}

bool dfs(int u){
	if (u == 0) return true;
	for (int v : adju[u]){
		if (dist[matchv[v]] == dist[u] + 1){
			if (dfs(matchv[v])){
				matchv[v] = u; 
				matchu[u] = v;
				return true;
			}
		}
	}
	dist[u] = INF;
	return false;
}

int hopcroft(){
	memset(&matchu, 0, sizeof matchu);
	memset(&matchv, 0, sizeof matchv);
	int result = 0;
	while (bfs()){
		for (int u = 1; u <= m; u++){
			if (matchu[u] == 0 and dfs(u))
				result++;
		}
	}
	return result;
}



bool fecho[MAXN][MAXN];
vi adj[MAXN];

void dfs_clo(int src, int v){
	fecho[src][v] = 1;

	// cout<<"visitei "<<src<<' '<<v<<endl;

	for (int x : adj[v])
		if (!fecho[src][x])
			dfs_clo(src, x);
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n;

	m = n;

	// dbg(n);

	int k, a;
	frr(i, n){
		cin>>k;
		fr(j, k){
			cin>>a;
			// cout<<"kkk "<<i<<' '<<a+1<<endl;
			adju[i].pb(a + 1);
		}
	}

	// chapa;
	// frr(i, n){
	// 	dbg(adj[i].size());
	// 	dfs_clo(i, i);
	// }

	// frr(i, n)
	// 	frr(j, n)
	// 		if (fecho[i][j] and i != j){
	// 			cout<<"emp "<<i<<' '<<j<<endl;
	// 			adju[i].pb(j);
	// 		}

	// dbg(hopcroft());		

	cout<< n - hopcroft()<<endl;			
}