#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define endl '\n'
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


struct circle{
	point c; coord r;
	circle() {} circle(point _c, coord _r): c(_c), r(_r) {}
	
	bool intsec(circle b){ // circunference
		return ((sign((c - b.c).norm() - (r + b.r)) <= 0) and 
		(sign((c - b.c).norm() - fabs(r - b.r)) >= 0)); }

	bool contain(point p){
		if(sign((p - c).norm() - r) <= 0) return true;
		return false;
	}
	
	vector<point> get_intsec(line l){ 
		coord d = l.dist(c);
		if (sign(d - r) > 0) return {};
		point proj = l.get_intsec((l.get_perp()).get_parall(c)); // prection of the center in the line 
		if (sign(d - r) == 0)return {proj};
		point aux = ((l.p).rot90()/(l.p.norm())) * sqrt(r * r - d * d);
		return {proj + aux, proj - aux};
	}	

	vector<point> get_intsec(circle o){
		if ((*this).intsec(o) == 0) return {};
		long double d2 = (c - o.c).norm2();
		long double tht = acos((r*r + d2 - o.r*o.r) / sqrt(4.0*r*r*d2));
		point vec = ((o.c - c)/(o.c - c).norm()) * r;
		return {c + vec.rot(tht),c + vec.rot(-tht)};
	}

	vector<point> get_tan(point p){ // tangent points
		long double d2 = (c - p).norm2();
		if (sign(d2 - r * r) < 0) return {};
		if (sign(d2 - r * r) == 0) return {p};
		long double tht = acos(sqrt((r*r)/d2));
		point vec = ((p - c)/(p - c).norm()) * r;
		return {c + vec.rot(tht),c + vec.rot(-tht)};
	}
};	

circle circuns_triang(point a, point b, point c){ // circunscribed circle of a triangle
	line l1 = (line(a, b).get_perp()).get_parall((a + b)/2);
	line l2 = (line(a, c).get_perp()).get_parall((a + c)/2);
	point cnt = l1.get_intsec(l2);
	cnt.print();
	return circle(cnt, (a - cnt).norm());
}

circle inscrib_triang(point a, point b, point c){ // inscribed circle of a triangle
	coord lc = (b - a).norm(), la = (c - b).norm(), lb = (a - c).norm();
	point cnt = point(la*a.x+lb*b.x+lc*c.x, la*a.y+lb*b.y+lc*c.y) / (la + lb + lc);
	return circle(cnt, segment(a, b).dist(cnt));
}

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

int main(){

	fastio;

	cout << setprecision(12) << fixed;

	coord r;
	point a, b, c;
	cin >> r;
	cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;

	circle Ca = circle(a, r);
	circle Cb = circle(b, r);
	circle Cc = circle(c, r);

	vector<point> vc = Ca.get_intsec(Cb);
	vector<point> vb = Ca.get_intsec(Cc);
	vector<point> va = Cb.get_intsec(Cc);

	bool deu = false;
	point ans;

	for(auto x : vc){
		if(Cc.contain(x)){
			deu = true;
			ans = x;
		}
	}


	for(auto x : vb){
		if(Cb.contain(x)){
			deu = true;
			ans = x;
		}
	}


	for(auto x : va){
		if(Ca.contain(x)){
			deu = true;
			ans = x;
		}
	}

	if(deu){
		cout << "YES" << endl;
		ans.print();
	}
	else{
		cout << "NO" << endl;
	}



}
