#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

using coord = long double;
const long double pi = acos(-1);
const long double EPS = 1e-8;

int sign(coord x){return (x > EPS) - (x < -EPS);}

struct point {
	coord x, y;
	point() : x(0), y(0) {} 
	point (coord _x, coord _y): x(_x), y(_y) {}

	inline point operator+ (point p) {return {x + p.x, y + p.y}; }
	inline point operator- (point p) {return {x - p.x, y - p.y}; }

	inline void operator= (point p)  {x = p.x; y = p.y; }

	inline void print () { cout << x << ' ' << y << '\n';}
};

point uni(coord theta){
	return {cos(theta), sin(theta)};
}

int n;
point pos[1010];
int sz[1010];
int pai[1010];
vi adj[1010];

void dfs_sz(int u, int p){
	pai[u] = p;
	sz[u] = 1;
	for(auto x: adj[u]){
		if(x != p) dfs_sz(x, u);
		if(x != p) sz[u] += sz[x];
	} 
}

void dfs(point p, int v, coord lo, coord hi){
	pos[v] = p;

	int tam = sz[v] - 1;
	coord step = (hi - lo)/tam;

	coord lo_at = lo;

	for(auto x: adj[v]){
		if(x == pai[v]) continue;
		coord hi_at = lo_at + step*sz[x];
		dfs(p + uni((hi_at + lo_at)/2), x, lo_at, hi_at);
		lo_at = hi_at;
	}

}

int main(){

	fastio;

	cout << setprecision(10) << fixed;

	cin >> n;

	fr(i,n - 1){
		int u, w;
		cin >> u >> w;
		adj[u].pb(w);
		adj[w].pb(u);
	}

	dfs_sz(1, -1);

	point ori = {0,0};

	dfs(ori, 1, 0, 2*pi);

	frr(i,n){
		pos[i].print();
	}
}
