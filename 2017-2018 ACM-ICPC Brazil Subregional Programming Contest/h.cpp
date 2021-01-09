#include "bits/stdc++.h"
using namespace std;

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
const int MAXN = 2e2 + 10;

using coord = long ll;
const long double pi = acos(-1);
const coord EPS = 1e-8;

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

int deg[MAXN], memo[MAXN];
vi adj[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	ll n, a, b;

	cin>>n>>a>>b;

	vector<point> p;

	ll x, y;
	fr(i, n){
		cin>>x>>y;
		p.push_back(point(x, y));
	}

	point pa = point({a, 0}), pb = point({b, 0});

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (( ((p[j] - pa) ^ (p[i] - pa)) > 0) and (((p[i] - pb) ^ (p[j] - pb)) > 0) ){
				adj[i].push_back(j);
				deg[j]++;
			}

	queue<int> fila;
	
	fr(i, n)
		if (deg[i] == 0){
			memo[i] = 1;
			fila.push(i);
		}

	int ans = 0, vtx;	
	while (!fila.empty()){
		vtx = fila.front();
		fila.pop();

		ans = max(ans, memo[vtx]);

		for (int e : adj[vtx]){
			memo[e] = max(memo[e], memo[vtx] + 1);
			deg[e]--;
			
			if (deg[e] == 0)
				fila.push(e);
		}			
	}			

	cout<<ans<<endl;
}