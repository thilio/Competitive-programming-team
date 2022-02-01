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

void swap(point &a, point &b){ point aux = a; a = b; b = aux; }

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
	
	int ccw(point p){ return((b - a).ccw(p - a)); } // ccw  1 left, 0 over, -1 right  of seg a->b

	bool intsec(segment q){ segment p = *this;
		if (p.contains(q.a) or p.contains(q.b) or q.contains(p.a) or q.contains(p.b)) return true;
		return p.ccw(q.a) * p.ccw(q.b) == -1 and q.ccw(p.a) * q.ccw(p.b) == -1;	
	}
	
	coord len2(){ return (a - b).norm2(); }

	long double dist(segment q){segment p = *this; 
		return p.intsec(q)? 0 : min({p.dist(q.a), p.dist(q.b), q.dist(p.a), q.dist(p.b)});	}

	long double dist(point p){
		if (sign(((p - a) * (b - a))) >= 0 and sign((p - b) * (a - b)) >= 0)
			return abs((p - a) ^ (b - a)) / (b - a).norm();
		return min((p - a).norm(), (p - b).norm());
	}

	line getline(){return line(a, b); }
};



vector<point> gen(int ns){
	point p = point(1, 0);

	double tht = 2.0*pi/ns;

	vector<point> ans = {p};

	fr(i, ns - 1){
		p = p.rot(tht);
		ans.pb(p);
	}

	reverse(all(ans));

	return ans;
}

int n;
vector<point> pnts, now;

coord mxdst = 2e8;


bool pol_contain(vector<point> &pol, point p){ // pol must be in clockwise order
	int sz = pol.size();
	segment b = segment(point(0, 0), p);

	fr(i, sz){
		segment a = segment(pol[i], pol[(i + 1) % sz]);

		if (a.intsec(b))
			return 0;
	}

	return 1;
}

int ninside(vector<point> &pol){
	int ans = 0;
	for (auto p : pnts)
		ans += pol_contain(pol, p);
	return ans;
}

coord area(vector<point> &pol){
	coord ans = 0;
	int sz = pol.size();

	fr(i, sz)
		ans += pol[i] ^ pol[(i + 1) % sz];

	ans /= 2;
	return abs(ans);	
}


coord test(int ns){
	vector<point> base = gen(ns);
	vector<point> now = base;

	coord ini = 0, fim = mxdst, bst = 0;

	fr(i, 110){
		coord meio = (ini + fim)/2;
		
		fr(j, ns)
			now[j] = base[j] * meio;

		if (ninside(now) > 0)
			fim = meio;
		else{
			bst = meio;
			ini = meio;
		}
	}


	fr(j, ns)
		now[j] = base[j] * bst;

	coord ain = area(now);

	ini = 0, fim = mxdst, bst = mxdst;

	fr(i, 110){
		coord meio = (ini + fim)/2;
		fr(j, ns)
			now[j] = base[j] * meio;

		if (ninside(now) < n)
			ini = meio;
		else{
			bst = meio;
			fim = meio;
		}
	}

	fr(j, ns)
		now[j] = base[j] * bst;

	coord aout = area(now);
	
	return ain/aout;
}


signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n;

	fr(i, n){
		int x, y;
		cin>>x>>y;
		pnts.pb(point(x, y));
	}

	int bst = 0;
	coord bsta = 0;

	for (int s = 3; s <= 8; s++){
		coord aux = test(s);
		if (aux > bsta){
			bsta = aux;
			bst = s;
		}
	}

	cout<<setprecision(12)<<fixed;
	cout<<bst<<' '<<bsta<<endl;
}