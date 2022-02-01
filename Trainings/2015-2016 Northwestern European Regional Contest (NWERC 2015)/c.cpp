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

using coord = long long;
const long double EPS = 1e-8;

int sign(coord x) {return (x > EPS) - (x < -EPS);}

struct point {
	coord x,y;
	point(): x(0), y(0) {} 
	point(coord _x, coord _y): x(_x), y(_y) {}

	inline point operator+(point p){return {x + p.x, y + p.y}; }
	inline point operator-(point p){return {x -  p.x, y -p.y}; }

	inline coord operator*(point p) {return x*p.x + y*p.y;}
	inline coord operator^(point p) {return x*p.y - y*p.x;}

	inline int ccw(point p){return sign(*this ^ p);}
	inline bool operator==(point p) {return x == p.x && y == p.y;}
	inline void operator= (point p){x = p.x; y = p.y;}


};

struct segment {
	point a, b; 
	segment() {}
	segment(point _a, point _b): a(_a), b(_b) {}

	bool contains(point p) {return sign(((p - a)^(b -a))) == 0 && sign(((p-a)*(b - a))) >= 0 && sign(((p-b)*(a-b)))>= 0;}
	int ccw (point p){return (b - a).ccw(p);}

	bool intsec(segment q){
		segment p = *this;
		if(p.contains(q.a) || p.contains(q.b) || q.contains(p.a) || q.contains(p.b))
			return true;
		return p.ccw(q.a - p.a)*p.ccw(q.b -p.a) == -1 && q.ccw(p.a - q.a)*q.ccw(p.b - q.a) == -1;
	}
};

int wn;
point w[1010];
int pn;
segment p[1010];
vi adj[1010];
int vis[1010];

bool dfs(int v, int p){
	vis[v] = p;
	bool ok = true;
	for(auto x: adj[v]){
		if(vis[x] == p) return false;
		if(vis[x] == 3 - p) continue;
		ok = ok&dfs(x, 3 - p);
	}
	return ok;
}

int main(){

	fastio;

	cin >> wn >> pn;
	frr(i,wn){
		cin >> w[i].x >> w[i].y;
	}
	frr(i, pn){
		int s; point b;
		cin >> s >> b.x >> b.y;
		p[i] = {w[s], b};	
	}

	frr(i,pn){
		frr(j,pn){
			if(p[i].a == p[j].a) continue;
			if(p[i].intsec(p[j])){
				adj[i].pb(j);
			}
		}
	}

	frr(i,pn){
	//	cout << i << ':';
	//	for(auto x: adj[i]) cout << x << ' ';
	//	gnl;	
	}

	bool ok = true;

	frr(i,pn){
		if(vis[i] == 0){
			ok = ok&dfs(i, 1);
		}
	}

	if(ok) cout << "possible" << endl;
	if(!ok) cout << "impossible" << endl;


}
