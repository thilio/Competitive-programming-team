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

using coord = ll;
const long double pi = acos(-1);
const long double EPS = 0;

int sign(coord x) { return (x > 0) - (x < 0); }
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

	inline bool operator<(point &p){ return sign(x - p.x) != 0 ? sign(x - p.x) < 0 : sign(y - p.y) < 0; } // lex_sort
	inline bool operator==(point p){ return sign(x - p.x) == 0 and sign(y - p.y) == 0; }

	inline void print(){ cout<<x<<' '<<y<<'\n'; }
};

void swap(point &a, point &b){ point aux = a; a = b; b = aux; }


int n, m;

vector<point> pnts[110];


bool comp(int id){
	set<pair<ll, ll>> q;

	for (int i = 0; i < m - 1; i++){
		point a = pnts[id][i] - pnts[id][m - 1];
	
		point b = pnts[0][i] - pnts[0][m - 1];
	
		if ((a^b) != 0)
			return false;
		if ((a * b) < 0)
			return false;

		ll va = a.norm2();
		ll vb = b.norm2();
		ll vc = __gcd(va, vb);
		va /= vc;
		vb /= vc;

		q.insert({va, vb});
	}

	return q.size() == 1;
}

signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>m;

	coord x, y;
	fr(i, n + 1){
		fr(j, m){
			cin>>x>>y;
			pnts[i].pb(point(x, y));
		}
		sort(all(pnts[i]));
	}

	frr(i, n)
		if (m == 1 or comp(i))
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
}