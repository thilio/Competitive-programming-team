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

vector<int> adju[MAXN];
int matchu[MAXN], matchv[MAXN], coveru[MAXN], coverv[MAXN]; 
int dist[MAXN], q[MAXN];
int m, n;

bool bfs(){
	int st = 0, en = 0;
	for (int u = 1; u <= m; u++) {
		if (matchu[u] == 0) {
			dist[u] = 0; 
			q[en++] = u;
		}
		else dist[u] = INF;
	}
	dist[0] = INF;
	while (en > st) {
		int u = q[st++];
		if (dist[u] >= dist[0]) 
			continue;
		for (int v : adju[u]) {
			if (dist[matchv[v]] == INF) {
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

int hopcroftKarp() {
	memset(&matchu, 0, sizeof matchu);
	memset(&matchv, 0, sizeof matchv);
	int result = 0;
	while (bfs()){
		for (int u = 1; u <= m; u++) {
			if (matchu[u] == 0 and dfs(u))
				result++;
		}
	}

	return result;
}


int mx[4] = {1, -1, 0, 0};
int my[4] = {0, 0, 1, -1};
int r, c, id[50][50];
char mapa[50][50];

bool valid(int x, int y){
	if (x < 0 or y < 0)
		return false;
	if (x >= r or y >= c)
		return false;
	return true;
}

void dfs_fill(int x, int y){
	mapa[x][y] = 'W';

	int i, j;
	fr(k, 4){
		i = x + mx[k];
		j = y + my[k];

		if (valid(i, j)){
			if (mapa[i][j] == 'L')
				dfs_fill(i, j);
			else if (mapa[i][j] == 'C')
				mapa[i][j] = 'W';
		}
	}
}

int32_t main(){
	fastio;

	cin>>r>>c;

	string s;
	fr(i, r){
		cin>>s;
		fr(j, c)
			mapa[i][j] = s[j];
	}

	int ans = 0;
	fr(i, r)
		fr(j, c)
			if (mapa[i][j] == 'L'){
				dfs_fill(i, j);
				ans++;
			}

	n = m = 0;		
	
	int x, y;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++){
			if (mapa[i][j] != 'C')
				continue;

			if ((i + j) % 2){
				m++;
				fr(k, 4){
					x = i + mx[k];
					y = j + my[k];
					if (valid(x, y) and mapa[x][y] == 'C'){
						if (id[x][y] == 0)
							id[x][y] = ++n;
						adju[m].pb(id[x][y]);
					}
				}
			}
			else if (id[i][j] == 0)
				id[i][j] = ++n;
	}

	ans += m + n - hopcroftKarp();
	
	cout<<ans<<endl;			
}