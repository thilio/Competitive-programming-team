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
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

// Basic structures and operations for geometry
using namespace std;

using coord = long long int;
const long double pi = acos(-1);
const long double EPS = 0;

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
	bool intsec(segment q){ segment p = *this;
		if (p.contains(q.a) or p.contains(q.b) or q.contains(p.a) or q.contains(p.b)) return true;
		return p.ccw(q.a-p.a)*p.ccw(q.b-p.a) == -1 and q.ccw(p.a-q.a)*q.ccw(p.b-q.a) == -1;	
	}

	int ccw(point p){ return((b - a).ccw(p - a)); } // ccw  1 left, 0 over, -1 right  of seg a->b

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

// Sort by augment angle related to o
struct comparator{
	point o;
	comparator(point _o): o(_o){}
	bool operator()(point a, point b){
		if (sign((a - o) ^ (b - o)) != 0)
			return sign((a - o) ^ (b - o)) > 0;
		return sign((a - o).norm2() - (b - o).norm2()) < 0;
	}
};

// build convex hull in nlog(n), n > 1
vector<point> convex_hull(vector<point> v, int border_in){ // should border be in convex?
	swap(v[0], *min_element(all(v))); // lex_sort
	sort(v.begin() + 1, v.end(), comparator(v[0]));
	int sz = 2, s, nv = v.size();
	if (border_in){
		for (s = nv - 1; s > 1 and sign((v[s] - v[0]) ^ (v[s - 1] - v[0])) == 0; s--);
		reverse(v.begin() + s, v.end());	
	}
	vector<point> hull = {v[0], v[1]};
	for (int i = 2; i < nv; i++)
		if (sz < 2)
			hull.push_back(v[i]), sz++;
		else if (sign((hull[sz - 1] - hull[sz - 2]) ^ (v[i] - hull[sz - 1])) >= 1 - border_in)
			hull.push_back(v[i]), sz++;
		else
			hull.pop_back(), i--, sz--;
	return hull;	
}

// check if a is conteined in polygon in O(log(n))
vector<point> pol_contain(vector<point> &pol, point a){ // pol must be in clockwise order
	int r = pol.size() - 1, l = 1, meio;
	while (r - l > 1){
		meio = (r + l) / 2;
		if (segment(pol[0], pol[meio]).ccw(a) >= 0) r = meio;
		else l = meio;
	}
	if (r == l){
		if (segment(pol[0], pol[r]).contains(a))
			return {pol[0], pol[r]};
		return {};
	}
	else{
		coord a1 =	fabs((pol[r] - pol[0]) ^ (pol[l] - pol[0]));
		coord a2 =	fabs((pol[r] - a) ^ (pol[l] - a)) +
					fabs((pol[l] - a) ^ (pol[0] - a)) +
					fabs((pol[0] - a) ^ (pol[r] - a));
		if (sign(a1 - a2) == 0)
			return {pol[0], pol[l], pol[r]};
		return {};				
	}
}

void solve(){
	int n, a, d;

	cin>>n>>a>>d;

	vector<point> pnts;
	int x, y;

	for (int i = 0; i < n; i++){
		cin>>x>>y;
		pnts.pb(point(x, y));
	}

	pnts.pb(point(0, 0));
	vector<point> chull = convex_hull(pnts, 0); // sem borda;
	// vetor retornado em anti-horario
	reverse(chull.begin() + 1, chull.end()); // agora em horario
	pnts.pop_back();	


	vector<point> trg = pol_contain(chull, point(a, d));
	if (trg.size() == 0){
		cout<<"N"<<endl;
		return;
	}

	point pnt = point(a, d);

	vector<pair<point, double>> ans;
	if (trg.size() == 2){ // convex hull com 2 pontos
		double t = ((double) pnt.x) / ((double) trg[1].x);
		ans.pb({trg[1], t});
		ans.pb({point(-1, -1), -1}); // dummy
	}
	else{
		double t, t1;
		point xx = trg[1].rot90(); 
		point yy = trg[2].rot90();
		
		t = ((double) (pnt * yy))/((double) (yy * trg[1]));
		t1 = ((double) (pnt * xx))/((double) (xx * trg[2]));
		
		ans.pb({trg[1], t});
		ans.pb({trg[2], t1});
	}

	// imprimir
	bool ok, ok1;
	ok = ok1 = 0;

	cout<<setprecision(9)<<fixed;

	cout<<"Y"<<endl;
	for (auto x : pnts){
		if (x == ans[0].fst and !ok){
			cout<<ans[0].snd<<endl;
			ok = 1;
		}
		else if (x == ans[1].fst and !ok1){
			cout<<ans[1].snd<<endl;
			ok1 = 1;
		}
		else
			cout<<0<<endl;
	}
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int T;
	cin>>T;

	while (T--)
		solve();
}