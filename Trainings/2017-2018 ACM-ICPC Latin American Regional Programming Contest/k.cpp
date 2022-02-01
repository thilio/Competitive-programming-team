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

int r, c;
bool mapa[22][22];

int mx[4] = {1, -1, 0, 0};
int my[4] = {0, 0, -1, 1};

bool valid(int x, int y){
	return (0 <= x and x < r ) and (0 <= y and y < c);
}

int crd(int x, int y){
	return 2 * (x * c + y + 1);
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>r>>c;

	string s;

	fr(i, r){
		cin>>s;
		fr(j, c)
			mapa[i][j] = (s[j] == 'o');
	}

	int rn, rm;
	rn = rm = n = m = 0;

	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++){
			if ((i + j) % 2 == 0) // lado da partição
				rn += 1 + !mapa[i][j];
			else{
				rm += 1 + !mapa[i][j];
			
				for (int k = 0; k < 4; k++){
					int x = i + mx[k];
					int y = j + my[k];

					if (valid(x, y)){
				
						adju[crd(i, j)].pb(crd(x, y));
					
						if (!mapa[i][j])
							adju[crd(i, j) + 1].pb(crd(x, y));
						
						if (!mapa[x][y])
							adju[crd(i, j)].pb(crd(x, y) + 1);
						
						if (!mapa[i][j] and !mapa[x][y])
							adju[crd(i, j) + 1].pb(crd(x, y) + 1);
					}
				}
			}
		}

	if (rn != rm){
		cout<<"N"<<endl;
		return 0;
	}

	n = 5 * r * c;
	m = 5 * r * c;

	if (hopcroftKarp() == rn)	
		cout<<"Y"<<endl;
	else
		cout<<"N"<<endl;

}	