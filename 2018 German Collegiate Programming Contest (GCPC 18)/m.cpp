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
const int MAXN = 1e6 + 10;

int id[MAXN], sz[MAXN], his[MAXN];
int find(int a, int t){
	if (id[a] == a) return a;
	if (his[a] > t) return a;

	return find(id[a], t);
}

void merge(int a, int b, int t){
	a = find(a, t);
	b = find(b, t);
	if (a == b)
		return;
	if (sz[a] < sz[b])
		swap(a, b);
	his[b] = t;
	sz[a] += sz[b];
	id[b] = a;
}

int qual_tempo(int a, int b){
	int bst, l, r, meio;
	l = 1;
	r = bst = MAXN;

	while (l <= r){
		meio = (l + r)/2;
		if (find(a, meio) != find(b, meio))
			l = meio + 1;
		else{
			r = meio - 1;
			bst = meio;
		}
	}
	return bst;
}

int n, m, q, mapa[555][555];
vii hgt[MAXN];

int mx[4] = {1, -1, 0, 0};
int my[4] = {0, 0, 1, -1};

int crd(int x, int y){
	return x * m + y;
}

bool valid(int x, int y){
	if (x < 0 or y < 0)
		return false;
	if (x >= n or y >= m)
		return false;
	return true;
}

int32_t main(){
	fastio;

	fr(i, MAXN){
		id[i] = i;
		sz[i] = 1;
	    his[i] = 0;
	}

	cin>>n>>m>>q;

	fr(i, n){
		fr(j, m){
			cin>>mapa[i][j];
			hgt[ mapa[i][j] ].pb({i, j});
		}
	}

	int x, y;
	for (int t = 1; t < MAXN; t++){
		for (auto at : hgt[t]){
			fr(k, 4){
				x = at.fst + mx[k];
				y = at.snd + my[k];
				if (valid(x, y) and mapa[x][y] <= t)
					merge( crd(at.fst, at.snd), crd(x, y), t); 
			}
		}
	}

	int a, b;
	while (q--){
		cin>>x>>y>>a>>b;
		x--, y--, a--, b--;
		if (x == a and y == b)
			cout<<mapa[x][y]<<endl;
		else
			cout<<qual_tempo(crd(x, y), crd(a, b))<<endl;
	}
}