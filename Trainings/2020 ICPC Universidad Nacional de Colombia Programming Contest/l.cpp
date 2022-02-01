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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 2e3 + 10;

int n, m;
int ex, ey, sx, sy;
char mapa[MAXN][MAXN];

int U[MAXN][MAXN], D[MAXN][MAXN], L[MAXN][MAXN], R[MAXN][MAXN];
int dist[MAXN][MAXN];

int bfs(){
	fr(i, n)
		fr(j, m)
			dist[i][j] = -1;

	queue<pii> fila;
	
	fila.push({sx, sy});
	dist[sx][sy] = 0;

	int x, y;
	while (!fila.empty()){
		tie(x, y) = fila.front();
		fila.pop();

		if (L[x][y] != -1 and dist[x][L[x][y]] == -1){
			dist[x][L[x][y]] = dist[x][y] + 1;
			fila.push({x, L[x][y]});
		}
		if (R[x][y] != -1 and dist[x][R[x][y]] == -1){
			dist[x][R[x][y]] = dist[x][y] + 1;
			fila.push({x, R[x][y]});
		}
		if (U[x][y] != -1 and dist[U[x][y]][y] == -1){
			dist[U[x][y]][y] = dist[x][y] + 1;
			fila.push({U[x][y], y});
		}
		if (D[x][y] != -1 and dist[D[x][y]][y] == -1){
			dist[D[x][y]][y] = dist[x][y] + 1;
			fila.push({D[x][y], y});
		}
	}
	return dist[ex][ey];
}


int vis[MAXN][MAXN];
string t;
void dfs(int x, int y){
	if (x == ex and y == ey){
		cout<<t<<endl;
		exit(0);
	}

	if (vis[x][y])
		return;
	vis[x][y] = 1;

	// lexicografico
	if (D[x][y] != -1 and dist[D[x][y]][y] == dist[x][y] + 1){
		t.pb('D');
		dfs(D[x][y], y);
		t.pop_back();
	}
	if (L[x][y] != -1 and dist[x][L[x][y]] == dist[x][y] + 1){
		t.pb('L');
		dfs(x, L[x][y]);
		t.pop_back();
	}
	if (R[x][y] != -1 and dist[x][R[x][y]] == dist[x][y] + 1){
		t.pb('R');
		dfs(x, R[x][y]);
		t.pop_back();
	}
	if (U[x][y] != -1 and dist[U[x][y]][y] == dist[x][y] + 1){
		t.pb('U');
		dfs(U[x][y], y);
		t.pop_back();
	}
}

int32_t main(){
	fastio;
	cin>>n>>m;

	string s;
	fr(i, n){
		cin>>s;
		fr(j, m){
			mapa[i][j] = s[j];
			if (s[j] == 'E'){
				ex = i;
				ey = j;
			}
			if (s[j] == 'S'){
				sx = i;
				sy = j;
			}
		}
	}

	int at = -1;
	for(int i = 0; i < n; i++){
		at = -1;
		for (int j = 0; j < m; j++){ // rght -> left
			L[i][j] = at;
			if (mapa[i][j] != 'X')
				at = j;
		}
		at = -1;
		for (int j = m - 1; j >= 0; j--){// left -> right
			R[i][j] = at;
			if (mapa[i][j] != 'X')
				at = j;
		}
	}

	for (int j = 0; j < m; j++){
		at = -1;
		for (int i = 0; i < n; i++){ // up -> down
			U[i][j] = at;
			if (mapa[i][j] != 'X')
				at = i;
		}
		at = -1;
		for (int i = n - 1; i >= 0; i--){ // down -> up
			D[i][j] = at;
			if (mapa[i][j] != 'X')
				at = i;
		}
	}

	int ans = bfs();

	cout<<ans<<endl;
	if (ans != -1)
		dfs(sx, sy);

}