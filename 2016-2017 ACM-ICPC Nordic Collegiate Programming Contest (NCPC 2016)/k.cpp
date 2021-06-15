#include "bits/stdc++.h"
using namespace std;

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

	inline bool operator<(point &p){ return sign(x - p.x) != 0 ? sign(x - p.x) < 0 : sign(y - p.y) < 0; } // lex_sort
	inline bool operator==(point p){ return sign(x - p.x) == 0 and sign(y - p.y) == 0; }

	inline void print(){ cout<<x<<' '<<y<<'\n'; }
};

void swap(point &a, point &b){ point aux = a; a = b; b = aux; }


struct segment {
	point a, b; // a != b
	segment() {} segment(point _a, point _b): a(_a), b(_b) {}
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

int n, m;
vector<segment> A, B;

coord tent(segment s, segment t, coord lamb){
	point ps = s.a*(1 - lamb) + s.b*lamb;
	point pt = t.a*(1 - lamb) + t.b*lamb;

	return (ps - pt).norm();
}

coord ternary(segment s, segment t){
	//if(s.a == point(6, 8)) olar;

	coord l = 0;
	coord r = 1;

	frr(i, 70){
		coord nl = l + (r - l)/3;
		coord nr = r - (r - l)/3;

		coord pl = tent(s, t, nl);
		coord pr = tent(s, t, nr);

		if(pr > pl){
			r = nr;
		}
		else l = nl;
	}

//	dbg(tent(s, t, 1));

	return tent(s, t, l);
}

int main(){

	fastio;

	cout << setprecision(12) << fixed;
	
	cin >> n;
	point at, last;
	fr(i, n){
		cin >> at.x >> at.y;
		if(i != 0){
			A.pb(segment(last, at));
		}
		last = at;
	}

	cin >> m;
	fr(i, m){
		cin >> at.x >> at.y;
		if(i != 0){
			B.pb(segment(last, at));
		}
		last = at;
	}

	point a, b;
	a = A[0].a; b = B[0].a;
	int ia, ib;
	ia = ib = 0;

	coord ans = llINF;
	while(true){
		//a.print();
		//b.print();
		//gnl;
		if(ia == A.size() || ib == B.size()) break;
		if((a - A[ia].b).norm() <= (b - B[ib].b).norm() ){
			segment s = segment(a, A[ia].b);
			point bf = b + ((B[ib].b - b)/(B[ib].b - b).norm())*(A[ia].b - a).norm();
			segment t = segment(b, bf);

			b = bf;
			a = A[ia].b;
			ia++;

			if((B[ib].b - b).norm() <= EPS){
				b = B[ib].b;
				ib++;
			}

			ans = min(ans, ternary(s, t));
		}
		else{
			segment s = segment(b, B[ib].b);
			point af = a + ((A[ia].b - a)/(A[ia].b - a).norm())*(B[ib].b - b).norm();
			segment t = segment(a, af);

			a = af;
			b = B[ib].b;
			ib++;

			if((A[ia].b - a).norm() <= EPS){
				a = A[ia].b;
				ia++;
			}

			ans = min(ans, ternary(s, t));
		}
	}

	ans = min(ans, (b - a).norm());
	cout << ans << endl;



}
