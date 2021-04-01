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

using coord = long long int;

int sign(coord x){ return (x > 0) - (x < 0); }
 
struct point {
	coord x, y;
	point() : x(0), y(0) {} point(coord _x, coord _y) : x(_x), y(_y) {}
	inline point operator+(point p){ return {x + p.x, y + p.y};}
	inline point operator-(point p){ return {x - p.x, y - p.y};}
	
	inline coord operator*(point p){ return x * p.x + y * p.y; } 
	inline coord operator^(point p){ return x * p.y - y * p.x; } // this -> p

	inline int ccw(point p){ return sign(*this ^ p); }

	inline coord norm2(){return x * x + y * y; }

	inline bool operator<(point &p){ return sign(x - p.x) != 0 ? sign(x - p.x) < 0 : sign(y - p.y) < 0; } // lexsort

};

void swap(point &a, point &b){ point aux = a; a = b; b = aux; }

struct segment {
	point a, b;
	segment() {} segment(point _a, point _b): a(_a), b(_b) {}

	bool contains(point p){ return sign((p-a)^(b-a)) == 0 and sign((p-a)*(b-a)) >= 0 and sign((p-b)*(a-b)) >= 0; }

	int ccw(point p){ return((b - a).ccw(p - a)); } // ccw  correta
};


struct comparator{
	point o;
	comparator(point _o): o(_o){}
	bool operator()(point a, point b){
		if (sign((a - o) ^ (b - o)) != 0)
			return sign((a - o) ^ (b - o)) > 0;
		return sign((a - o).norm2() - (b - o).norm2()) < 0;
	}
};

vector<point> convex_hull(vector<point> v, int border_in){
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
			hull.pb(v[i]), sz++;
		else if (sign((hull[sz - 1] - hull[sz - 2]) ^ (v[i] - hull[sz - 1])) >= 1 - border_in)
			hull.pb(v[i]), sz++;
		else
			hull.pop_back(), i--, sz--;
	return hull;	
}

bool pol_contain(vector<point> &pol, point a){
	int r = pol.size() - 1, l = 1, meio;
	while (r - l > 1){
		meio = (r + l) / 2;
		if (segment(pol[0], pol[meio]).ccw(a) >= 0) r = meio;
		else l = meio;
	}
	if (r == l) return segment(pol[0], pol[r]).contains(a);
	else{
		coord a1 =	abs((pol[r] - pol[0]) ^ (pol[l] - pol[0]));
		coord a2 =	abs((pol[r] - a) ^ (pol[l] - a)) +
					abs((pol[l] - a) ^ (pol[0] - a)) +
					abs((pol[0] - a) ^ (pol[r] - a));
		return sign(a1 - a2) == 0;			
	}
}

int n, m;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n;

	vector<point> in;

	coord x, y;
	fr(i, n){
		cin>>x>>y;
		in.pb(point(x, y));
	}

	vector<point> chull = convex_hull(in, 0);
	reverse(all(chull));

	cin>>m;

	int ans = 0;
	fr(i, m){
		cin>>x>>y;
		ans += pol_contain(chull, point(x, y));
	}

	cout<<ans<<endl;
}