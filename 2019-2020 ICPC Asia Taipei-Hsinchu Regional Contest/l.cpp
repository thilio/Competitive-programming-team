#include "bits/stdc++.h"
using namespace std;

using coord = long long;
const long double pi = acos(-1);
const long double EPS = 1e-8;

#define all(x)	x.begin(),x.end()

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
	inline bool operator!=(point p){ return !(*this == p); }

	inline void print(){ cout<<x<<' '<<y<<'\n'; }
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

// build convex hull in nlog(n), n > 1, hull is in reverse clockwise order
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

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl

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

int n;
vector<point> v;
vector<point> h;

ll best_d[5000];
ll best_u[5000];

ll area_quad(vector<point>& p){
	//swap(p[0], *min_element(all(p))); // lex_sort
	//sort(p.begin() + 1, p.end(), comparator(p[0]));
	ll ans = 0;

	fr(i, p.size()){
		int nxt = (i + 1)%p.size();
		ans += p[i]^p[nxt];
	}

	return ans;

}

ll brute_3(){
	vector<point> p;
	p.pb(h[0]);
	p.pb(h[1]);
	p.pb(h[2]);

	ll ans = 0;

	fr(i, n){
		if(v[i] != h[0] && v[i] != h[1] && v[i] != h[2]){
			p.pb(v[i]);
			fr(i, 24){
				ans = max(ans, area_quad(p));
				next_permutation(all(p));	
			}
			p.pop_back();
		}
	}

	return ans;
}

int nxt(int i, int k){
	return (i + 1)%k;
}
int prev(int i, int k){
	return (i + k - 1)%k;
}

ll calip(int i){
	int k = h.size();
	int j = nxt(nxt(i, k), k);
	int b = nxt(i, k);

	for(; j != prev(i, k); j = nxt(j, k)){
		while(abs((h[j] - h[i])^(h[b] - h[i])) <= abs((h[j] - h[i])^(h[nxt(b, k)] - h[i])) && j != b) b = nxt(b, k);

		best_d[j] = abs((h[j] - h[i])^(h[b] - h[i]));
	}

	j = prev(prev(i, k), k);
	b = prev(i, k);

	for(; j != nxt(i, k); j = prev(j, k)){	
		while(abs((h[j] - h[i])^(h[b] - h[i])) <= abs((h[j] - h[i])^(h[prev(b, k)] - h[i])) && j != b) b = prev(b, k);

		best_u[j] = abs((h[j] - h[i])^(h[b] - h[i]));
	}

	ll ans = 0;
	j = nxt(nxt(i, k), k);
	for(; j != prev(i, k); j = nxt(j, k)){
		ans = max(ans, best_u[j] + best_d[j]);
	}

	return ans;
}

ll solve(){
	cin >> n;

	v.clear();
	v.resize(n);

	fr(i, n){
		cin >> v[i].x >> v[i].y;	
	}

	h = convex_hull(v, 1);

	if(h.size() <= 2){
		return 0;
	}

	if(h.size() == 3){
		return brute_3();
	}

	ll ans = 0;

	fr(i, h.size()) ans = max(ans, calip(i));

	return ans;
}

void print(ll x){
	cout << x/2;
	if(x&1) cout << ".5";
	gnl;
}

int main(){

	fastio;

	int T;
	cin >> T;
	while(T--){
		print(solve());
	}

}
