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
const int MAXN = 1e3 + 10;

int n, m, v;
int mx[4] = {1, -1, 0, 0};
int my[4] = {0, 0, 1, -1};

string mapa[MAXN];
int dist[MAXN][MAXN];

signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, m, v;
	cin>>n>>m>>v;


	int sx, sy, tx, ty;
	cin>>sx>>sy>>tx>>ty;


	fr(i, n)
		cin>>mapa[i];

	fr(i, n)
		fr(j, m)
			dist[i][j] = v + 1;


	sx--; sy--;
	tx--; ty--;


	dist[sx][sy] = 0;
	queue<pii> fila;
	fila.push({sx, sy});

	int x, y, xx, yy, d;
	while (!fila.empty()){
		tie(x, y) = fila.front();
		fila.pop();

		if (x == tx and y == ty){
			cout<<"Hello, Deimos!"<<endl;
			return 0;
		}

		d = dist[x][y] + 1;

		fr(k, 4){
			xx = x + mx[k];
			yy = y + my[k];
			if ((0 <= xx) and (xx < n) and (0 <= yy) and (yy < m) and (dist[xx][yy] > d)){
				dist[xx][yy] = d;
				if (mapa[xx][yy] == 'F')
					dist[xx][yy] = 0;

				fila.push({xx, yy});
			}
		}
	}

	cout<<"Dire victory"<<endl;
}