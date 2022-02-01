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
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(9e18) + 100;   
const int MAXN = 1e5 + 10;

using coord = ll;
const long double pi = acos(-1);
const long double EPS = 1e-8;

int sign(coord x) { return (x > EPS) - (x < -EPS); }
coord sq(coord x) { return x * x; }

struct point {
	coord x, y;
	point() : x(0), y(0) {} point(coord _x, coord _y): x(_x), y(_y) {}
	inline point operator+(point& p){ return {x + p.x, y + p.y}; }
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
	
	inline void print(){ cout<<x<<' '<<y<<'\n'; }
};

vector<point> v;

int32_t main(){
	fastio;
	int n;

	cin>>n;

	ll a, b;
	fr(i, n){
		cin>>a>>b;
		v.pb(point(a, b));
	}
	fr(i, n)
		v.pb(v[i]);
	n *= 2;	
	
	ll ans = llINF;
	for (int i = 0; i < n - 2; i++){
		ll aux = abs((v[i] - v[i + 1]) ^ (v[i + 2] - v[i]));
		ans = min(ans, aux);
	}	

	cout<<ans<<endl;
}