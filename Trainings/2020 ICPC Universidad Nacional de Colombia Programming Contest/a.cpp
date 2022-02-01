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
const int MAXN = 1e5 + 10;

using coord = long double;
const long double pi = acos(-1);
const long double EPS = 1e-8;

int sign(coord x) { return (x > EPS) - (x < -EPS); }
coord sq(coord x) { return x * x; }

struct point {
	coord x, y;
	point() : x(0), y(0) {} point(coord _x, coord _y): x(_x), y(_y) {}
	inline point operator+(point p){ return {x + p.x, y + p.y}; }
	inline point operator-(point& p){ return {x - p.x, y - p.y}; }
	inline point operator*(coord o){ return {x * o, y * o}; }
	inline point operator/(coord o){ return {x / o, y / o}; }
	inline void operator=(point& p){ x = p.x, y = p.y; }
	inline bool operator==(point& p){return sign(x - p.x) == 0 and sign(y - p.y) == 0; }

	inline coord operator*(point p){ return x * p.x + y * p.y; } // |a||b|cos(thta)
	inline coord operator^(point p){ return x * p.y - y * p.x; } // |a||b|sin(thta)

	inline int ccw(point p){ return sign(*this ^ p); } // ccw  -1 left, 0 over, 1 right

	inline long double norm(){ return hypot(x, y); }
	inline coord norm2(){ return x * x + y * y; }

	inline point rot90(){return {-y, x}; }
	inline point rot(long double ang){ return {cos(ang) * x - sin(ang) * y, sin(ang) * x + cos(ang) * y}; }
	inline point proj(point p){return p * (((*this) * p)/p.norm()); }

	inline void print(){ cout<<x<<' '<<y<<'\n'; }
};

struct line {
	point p; coord c; //p * <x,y> = c
	line() {} line(point _p, coord _c): p(_p), c(_c) {}
	line(point a, point b) : p((b - a).rot90()), c(p * a) {}
	line parll(point v){ return line(p, p * v); }// parallel line at point v
	line perp(){ return line(p.rot90(), c); }// perpendicular line

	bool contains(point v){ return sign(p * v - c) == 0; }
	bool intsec(line l){ return sign(p ^ l.p) != 0; } // can be the same line

	coord dist(point v){ return abs(p * v - c) / p.norm2(); }

	point get_intsec(line l){ coord d = p^l.p; return point((c*l.p.y - l.c*p.y)/d, (p.x*l.c - c*l.p.x)/d); }
};

struct segment {
	point a, b; // a != b
	segment() {} segment(point _a, point _b): a(_a), b(_b) {}

	bool contains(point p){ return sign((p-a)^(b-a)) == 0 and sign((p-a)*(b-a)) >= 0 and sign((p-b)*(a-b)) >= 0; }
	bool intsec(segment q){ segment p = *this;
		if (p.contains(q.a) or p.contains(q.b) or q.contains(p.a) or q.contains(p.b))
			return true;
		return p.ccw(q.a-p.a)*p.ccw(q.b-p.a) == -1 and q.ccw(p.a-q.a)*q.ccw(p.b-q.a) == -1;	
	}

	int ccw(point p){ return((b - a).ccw(p)); } // ccw  -1 left, 0 over, 1 right  of seg a->b

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

void swap(point &a, point &b){
	point c = a;
	a = b;
	b = c;
}

long double test(segment ab, segment ce, long double t){
	point a = (ab.a * t) + (ab.b * (1 - t));
	point b = (ce.a * t) + (ce.b * (1 - t));

	return (a - b).norm();
}

int32_t main(){
	fastio;

	int x, y;
	cin>>x>>y;
	point a = point(x, y);
	cin>>x>>y;
	point b = point(x, y);
	cin>>x>>y;
	point c = point(x, y);
	cin>>x>>y;
	point d = point(x, y);

	if ((a - b).norm2() > (c - d).norm2()){
		swap(a, c);
		swap(b, d);
	}

	segment ab = segment(a, b); // menor
	point e = ((d - c) / (d - c).norm()) * (a - b).norm(); // ce tem tamanho ab

	segment ce = segment(c, c + e); // parte 1
	segment ed = segment(c + e, d); // parte 2

	long double ans = (c - a).norm(); // distancia inicial

	long double l, r, k1, k2, d1, d2;
	int cnt = 1000;
	l = 0;
	r = 1;

	while (cnt--){
		k1 = l + (r - l)/3;
		k2 = r - (r - l)/3;

		d1 = test(ab, ce, k1);
		d2 = test(ab, ce, k2);

		if (d1 < d2)
			r = k2;
		else
			l = k1;
	}

	ans = min(ans, test(ab, ce, l)); // distancia no meio do caminho

	ans = min(ans, ed.dist(b)); // distancia ponto final para techo excedente

	cout<<setprecision(12)<<fixed;
	cout<<ans<<endl;	
}