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
const int MAXN = 2e5 + 10;

int mx[4] = {1, -1, 0, 0};
int my[4] = {0, 0, 1, -1};

int n, m, d;
vector<string> mapa;

bool valid(int x, int y){
	if (x >= n or y >= m)
		return false;
	if (x < 0 or y < 0)
		return false;
	return mapa[x][y] != 'M';
}

int crd(int x, int y){
	return x * m + y;
}

int dist[MAXN];

void dfs1(){
	memset(dist, -1, sizeof dist);
	queue<pii> fila;
	fr(i, n)
		fr(j, m)
			if (mapa[i][j] == 'M'){
				fila.push({i, j});
				dist[crd(i, j)] = 0;
			}
	int x, y;
	pii aux;
	while (!fila.empty()){
		aux = fila.front();
		fila.pop();

		if (dist[crd(aux.fst, aux.snd)] <= d)
			mapa[aux.fst][aux.snd] = 'M';

		fr(k, 4){
			x = aux.fst + mx[k];
			y = aux.snd + my[k];
			if (valid(x, y) and dist[crd(x, y)] == -1){
				dist[crd(x, y)] = dist[crd(aux.fst, aux.snd)] + 1;
				fila.push({x, y});
			}
		}
	}			
}

void dfs2(){
	memset(dist, -1, sizeof dist);
	queue<pii> fila;
	fr(i, n)
		fr(j, m)
			if (mapa[i][j] == 'S'){
				fila.push({i, j});
				dist[crd(i, j)] = 0;
			}
	int x, y;
	pii aux;
	while (!fila.empty()){
		aux = fila.front();
		fila.pop();

		fr(k, 4){
			x = aux.fst + mx[k];
			y = aux.snd + my[k];
			if (valid(x, y) and dist[crd(x, y)] == -1){
				dist[crd(x, y)] = dist[crd(aux.fst, aux.snd)] + 1;
				fila.push({x, y});
			}
		}
	}	

}

int32_t main(){
	fastio;
	cin>>n>>m>>d;
	mapa.resize(n);
	fr(i, n)
		cin>>mapa[i];
	
	dfs1();
	dfs2();

	fr(i, n)
		fr(j, m)
			if (mapa[i][j] == 'F'){
				cout<<dist[crd(i, j)]<<endl;
				return 0;
			}

	cout<<-1<<endl;		
}