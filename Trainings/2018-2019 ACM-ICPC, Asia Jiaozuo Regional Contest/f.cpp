#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

// #define endl '\n'
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
const int MAXN = 4e6 + 10;

int n, m, r, c, dist[MAXN];
vector<string> mapa;
vector<int> lin, col;
vi adj[MAXN];

inline int crd(int x, int y){ return x * m + y; }

void solve(){
	cin>>n>>m;
	for (int i = 0; i < n * m + 10; i++)
		adj[i].clear();

	string ssds;
	getline(cin, ssds);

	r = 4 * n + 3;
	c = 6 * m + 3;

	mapa.resize(r);

	fr(i, r){
		getline(cin, mapa[i]);
		// dbg(mapa[i]);
	}

	int cev = 4, cod = 10;	

	for (int j = 0; j < m; j++){
		if (j % 2 == 0){
			int l = 4;
			for (int i = 0; i < n - 1; i++){
				if (mapa[l][cev] == ' '){
					adj[crd(i, j)].pb(crd(i + 1, j));
					adj[crd(i + 1, j)].pb(crd(i, j));
				}
				l += 4;
			}
			cev += 12;	
		}
		else{
			int l = 6;
			for (int i = 0; i < n - 1; i++){
				if (mapa[l][cod] == ' '){
					adj[crd(i, j)].pb(crd(i + 1, j));
					adj[crd(i + 1, j)].pb(crd(i, j));
				}
				l += 4;
			}
			cod += 12;
		}
	}	

	// for (int i = 0; i < n * m; i++)
	// 	for (auto x : adj[i])
	// 		cout<<i<<' '<<x<<endl;


	for (int i = 0; i < 2 * n - 1; i++)
		for (int j = 0; j < m - 1; j++){
			int a = (i + 1)/2;
			int b = i/2;
			if (j % 2)
				swap(a, b);

			if (mapa[lin[i]][col[j]] == ' '){
				// cout<<a<<' '<<j<<' '<<b<<' '<<j + 1<<" ("<<i<<' '<<j<<")"<<" ("<<lin[i]<<' '<<col[j]<<")"<<endl;
				adj[crd(a, j)].pb(crd(b, j + 1));
				adj[crd(b, j + 1)].pb(crd(a, j));
			}
		}


	// for (int i = 0; i < n * m; i++)
	// 	for (auto x : adj[i])
	// 		cout<<i<<' '<<x<<endl;


	int start, end;
	cev = 4, cod = 10;	
	for (int j = 0; j < m; j++){
		if (j % 2 == 0){
			int l = 2;
			for (int i = 0; i < n; i++){
				if (mapa[l][cev] == 'S')
					start = crd(i, j);
				if (mapa[l][cev] == 'T')
					end = crd(i, j);
				l += 4;
			}
			cev += 12;	
		}
		else{
			int l = 4;
			for (int i = 0; i < n; i++){
				if (mapa[l][cod] == 'S')
					start = crd(i, j);
				if (mapa[l][cod] == 'T')
					end = crd(i, j);
				l += 4;
			}
			cod += 12;
		}
	}	
	// chapa;

	// dbg(start);
	// dbg(end);
	fr(i, n * m + 10)
		dist[i] = -1;

	queue<int> fila;
	fila.push({start});
	dist[start] = 1;

	int vtx, dst;
	while (!fila.empty()){
		vtx = fila.front();
		fila.pop();
		for (int x : adj[vtx])
			if (dist[x] == -1){
				dist[x] = dist[vtx] + 1;
				fila.push(x);
			}
	}

	cout<<dist[end]<<endl;	
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	// diagonais
	lin.pb(3);
	while (lin.back() < MAXN)
		lin.pb(lin.back() + 2);

	col.pb(7);
	while (col.back() < MAXN)
		col.pb(col.back() + 6);

	int T;
	cin>>T;
	while (T--)
		solve();
}