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

vector<int> adju[MAXN]; // adj da partição U
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

int hopcroftKarp(){
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

int mapa[110][110], lin[110][110];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);	

	int dim;
	while (cin>>dim){
		string s;
		fr(i, dim){
			cin>>s;
			fr(j, dim)
				mapa[i][j] = (s[j] == 'X'); // 1 se não pode, zero se pode;
		}

		n = 0;
		for (int i = 0; i < dim; i++){
			for (int j = 0; j < dim; j++){
				if (mapa[i][j] == 0){
					n++;
					while (j < dim and mapa[i][j] == 0){
						lin[i][j] = n;
						j++;
					}
				}
			}
		}

		m = 0;
		for (int j = 0; j < dim; j++){
			for (int i = 0; i < dim; i++){
				if (mapa[i][j] == 0){
					m++;
					adju[m].clear();
					while (i < dim and mapa[i][j] == 0){
						adju[m].pb(lin[i][j]);
						i++;
					}
				}
			}
		}
		cout<<hopcroftKarp()<<endl;
	}
}