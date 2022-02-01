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

int sign(coord x) { return (x > EPS) - (x < -EPS); }
coord sq(coord x) { return x * x; }

struct point {
	coord x, y;
	point() : x(0), y(0) {} point(coord _x, coord _y): x(_x), y(_y) {}
	inline point operator+(point p){ return {x + p.x, y + p.y}; }
	inline point operator-(point p){ return {x - p.x, y - p.y}; }
	inline point operator*(coord o){ return {x * o, y * o}; }
	inline point operator/(coord o){ return {x / o, y / o}; }
	inline void operator=(point p){ x = p.x, y = p.y; }

	inline coord operator*(point p){ return x * p.x + y * p.y; } // |a||b|cos(tht)
	inline coord operator^(point p){ return x * p.y - y * p.x; } // |a||b|sin(tht), this -> p

	inline int ccw(point p){ return sign(*this ^ p); } // ccw  1 left, 0 over, -1 right

	inline long double norm(){ return hypot(x, y); }
	inline coord norm2(){ return x * x + y * y; }

	inline point rot90(){return {-y, x}; }
	inline point rot(long double ang){ return {cos(ang) * x - sin(ang) * y, sin(ang) * x + cos(ang) * y}; }
	inline point project(point p){return p * (((*this) * p)/p.norm2()); }

	inline bool operator<(point &p){ return sign(x - p.x) != 0 ? sign(x - p.x) < 0 : sign(y - p.y) < 0; } // lex_sort
	inline bool operator==(point p){ return sign(x - p.x) == 0 and sign(y - p.y) == 0; }

	inline void print(){ cout<<x<<' '<<y<<'\n'; }
};

struct line {
	point p; coord c; //p * <x,y> = c
	line() {} line(point _p, coord _c): p(_p), c(_c) {}
	line(point a, point b) : p((b - a).rot90()), c(p * a) {}
	line get_parall(point v){ return line(p, p * v); }// parallel line at point v
	line get_perp(){ return line(p.rot90(), c); }// perpendicular line

	bool contains(point v){ return sign(p * v - c) == 0; }
	bool intsec(line l){ return sign(p ^ l.p) != 0; } // false if is the same line

	coord dist(point v){ return abs(p * v - c) / p.norm(); }

	point get_intsec(line l){ coord d = p^l.p; return point((c*l.p.y - l.c*p.y)/d, (p.x*l.c - c*l.p.x)/d); }
};

struct segment {
	point a, b; // a != b
	segment() {} segment(point _a, point _b): a(_a), b(_b) {}

	bool contains(point p){ return sign((p-a)^(b-a)) == 0 and sign((p-a)*(b-a)) >= 0 and sign((p-b)*(a-b)) >= 0; }
	
	int ccw(point p){ return((b - a).ccw(p)); } // ccw  -1 left, 0 over, 1 right  of seg a->b

	bool intsec(segment q){ segment p = *this;
		if (p.contains(q.a) or p.contains(q.b) or q.contains(p.a) or q.contains(p.b))
			return true;
		return p.ccw(q.a-p.a)*p.ccw(q.b-p.a) == -1 and q.ccw(p.a-q.a)*q.ccw(p.b-q.a) == -1;	
	}
	
	coord len2(){ return (a - b).norm2(); }

	coord dist(segment q){segment p = *this; 
		return p.intsec(q)? 0 : min({p.dist(q.a), p.dist(q.b), q.dist(p.a), q.dist(p.b)});	}

	coord dist(point p){
		if (sign(((p - a) * (b - a))) >= 0 and sign((p - b) * (a - b)) >= 0)
			return abs((p - a) ^ (b - a)) / (b - a).norm();
		return min((p - a).norm(), (p - b).norm());
	}

	line getline(){return line(a, b); }
};

vector<point> get_intsec(segment p, segment q){ // returns intersection points/segment
		if (!p.intsec(q)) return {};
		if (((p.b - p.a)^(q.b - q.a)) == 0){
			point a, b;
			if (p.contains(q.a) and p.contains(q.b)) a = q.a, b = q.b;
			else if (q.contains(p.a) and q.contains(p.b)) a = p.a, b = p.b;
			else if (p.contains(q.a) and q.contains(p.a)) a = q.a, b = p.a;
			else if (p.contains(q.a) and q.contains(p.b)) a = q.a, b = p.b;
			else if (p.contains(q.b) and q.contains(p.a)) a = q.b, b = p.a;
			else a = q.b, b = p.b;
			if (a == b) return {a};
			return {a, b};
		}	
		return {(p.getline()).get_intsec(q.getline())};
}

point reflect(segment k, point p){
	if(k.a.x == k.b.x){ // vertical
		coord delta = abs(k.a.x - p.x);
		if(p.x >= k.a.x) p.x -= 2*delta;
		else p.x += 2*delta;
	}

	if(k.a.y == k.b.y){ // horizontal
		coord delta = abs(k.a.y - p.y);
		if(p.y >= k.a.y) p.y -= 2*delta;
		else p.y += 2*delta;
	}

	return p;

}

segment s[8];
point hole;
bool ativo[8];
int n;

bool check(vi v){
	int sz = v.size();
	vector<point> t(sz + 1);
	t[sz] = hole;

	for(int i = sz - 1; i >= 0; i--){
		t[i] = reflect(s[v[i]], t[i + 1]);
	}

	point at = {0,0};
	ms(ativo, true);

	for(int i = 0; i < sz; i++){
		if((at - t[i]).norm() < EPS) return false;

		int next = v[i];
		coord mn = INF;
		int id = -1;
		point vou;

		for(int j = 0; j < n; j++){
			if(!ativo[j]) continue;
			vector<point> P = get_intsec({at, t[i]}, s[j]);
			if(P.size() != 1) continue;
			point p = P[0];

			coord dist = (at - p).norm();

			if(dist < mn){
				mn = dist;
				id = j;
				vou = p;
			}
		}

		if(id != next) return false;
		at = vou;
		ativo[next] = false;
	}

	for(int j = 0; j < n; j++){
		if(ativo[j]){
			segment aa = {at,hole};
			if(aa.intsec(s[j])) return false;
		}
	}

	return true;
}

int main(){

	fastio;
	cin >> n;
	cin >> hole.x >> hole.y;

	fr(i,n){
		point a,b;
		cin >> a.x >> a.y >> b.x >> b.y;
		s[i] = {a,b};
	}

	int ans = -1;

	for(int mask = 0; mask < (1 << n); mask++){
		vector<int> v;
		v.clear();
		fr(i,n){
			if(mask&(1 << i)) v.pb(i);
		}

		do{
			if(check(v)){
				ans = max(ans, __builtin_popcount(mask));
			}		
		}while(next_permutation(all(v)));
	}

	if(ans == -1) cout << "impossible"<< endl;
	else cout << ans << endl;

}
