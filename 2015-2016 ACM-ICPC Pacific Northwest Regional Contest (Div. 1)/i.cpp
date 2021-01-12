#include "bits/stdc++.h"
using namespace std;

using cord = long double;
const long double PI = acos(-1);
const long double EPS = 1e-8;

int signal(cord x) { return (x > EPS) - (x < -EPS); }

struct point {
	cord x,y;

	// Constructor
	point(cord _x, cord _y): x(_x), y(_y) {}
	point(): x(0), y(0) {}

	// Very basic operations
	void operator=  (const point p){x = p.x; y = p.y; }
	point operator+ (const point q){ return {x + q.x, y + q.y}; }
	point operator- (const point q){ return {x - q.x, y - q.y}; }
	point operator* (const cord s) { return {x*s, y*s}; }
	point operator/ (const cord s) { return {x/s, y/s}; }

	// Basic operations
	cord cross (const point p){ return (x*p.y - y*p.x); }
	cord dot (const point p)  { return (x*p.x + y*p.y); }

	point proj(point p) { return(p*(dot(p)/p.norm()));} // proj ponto this em p


	// Length operations
	cord norm()       { return (x*x + y*y); } // retorna quadrado
	long double len() { return hypot(x, y); } // retorna sqrt(norm)

	// Rotation operations
	point rotate90()              { return {-y,x}; }
	point rotate(long double ang) { return {cos(ang)*x - sin(ang)*y, sin(ang)*x + cos(ang)*y}; }
};

struct circle{
	point p; cord r;
	circle (point _p, cord _r): p(_p), r(_r) {}
	circle (): p({0,0}), r(0) {}


	int inter(circle c, point &q1, point &q2){ // 0 se nenhum, 1 se dois, 2 se infinitos; não funciona se r = 0.
		long double d = (c.p - p).norm();
		if(signal(d - (c.r + r)*(c.r + r)) > 0 || signal(d - (r - c.r)*(r - c.r)) < 0){
			q1 = {0,0}; q2 = {0,0}; return 0;
		}
		if(signal((p - c.p).norm()) == 0 && signal(r - c.r) == 0){
			q1= {0,0};q2 = {0,0}; return 2;
		}

		long double theta;

		theta = acos((c.r*c.r - r*r - d)/(long double)(-2*r*sqrt(d)));

		point dir = c.p - p;
		dir = dir/dir.len();
		dir = dir*r;

		q1 = p + dir.rotate(theta);
		q2 = p + dir.rotate(-theta);

		return 1;
	}

};

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

int id[5050], sz[5050];
circle c[5050];
vector<circle> candidates;
int mark[5050];

int find(int v){
	if(id[v] == v) return v;
	return id[v] = find(id[v]);
}

void merge(int u,int v){
	u = find(u);
	v = find(v);
	if(u == v) return;
	if(sz[u] >= sz[v]) swap(u,v);
	id[u] = v;
	sz[v] += sz[u];
}

int main(){

	fastio;

	int n;
	cin >> n;

	fr(i,n){
		id[i] = i;
		sz[i] = 1;
	}

	fr(i,n){
		point p;
		cin >> p.x >> p.y;
		c[i] = {p,1};
	}

	fr(i,n){
		fr(j,n){
			point a,b;
			if(c[i].inter(c[j],a,b) > 0){
				merge(i,j);	
			}
		}
	}

	fr(i,n){
		for(int j = i + 1; j < n; j++){
			if((c[i].p - c[j].p).norm() > 16 + EPS) continue;
			else if((c[i].p - c[j].p).norm() >= 16 - EPS){
				circle k;
				k.p = (c[i].p + c[j].p)/2;
				k.r = 2;
				candidates.pb(k);
			}
			else{
				circle ka,kb;
				circle ki,kj;
				ki.p = c[i].p;
				ki.r = 2;
				kj.p = c[j].p;
				kj.r = 2;
				int x = ki.inter(kj, ka.p, kb.p);
				ka.r = kb.r = 2;
				candidates.pb(ka);
				candidates.pb(kb);
			}
			//dbg(i);
		}
	}


	int ans = 0;

	fr(i,n) ans = max(ans,sz[find(i)] + 1);

	for(auto x: candidates){
		fr(i,n) mark[i] = 0;
		fr(i,n){
			if((c[i].p - x.p).norm() <= 4 + EPS) mark[find(i)] = 1;
		}

		int at = 1;
		fr(i,n) if(mark[i]) at += sz[i];
		ans = max(ans,at);
	}

	cout << ans << endl;




}
