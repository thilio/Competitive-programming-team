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

using coord = long long int;
const long double pi = acos(-1);
const coord EPS = 1e-8;

int sign(coord x) {return (x > EPS) - (x < -EPS);}
coord sq(coord x) {return x * x;}

struct point{
	coord x, y;
	point() : x(0), y(0) {} point(coord _x, coord _y) : x(_x), y(_y) {}
	inline point operator+(point p) {return {x + p.x, y + p.y}; }
	inline point operator-(point p) {return {x - p.x, y - p.y}; }
	inline point operator*(coord o) {return {x * o, y * o}; }
	inline point operator/(coord o) {return {x / o, y / o}; }
	inline void operator=(point p){x = p.x, y = p.y;}

	inline coord operator*(point p) { return x * p.x + y * p.y; }
	inline coord operator^(point p){ return x * p.y - y * p.x; }

	inline int ccw(point p){ return sign(*this^p);}

	inline long double norm() {return hypot(x, y); }
	inline coord norm2(){ return x * x + y * y; }
};

int n;
vector<point> v;

int ant(int i){
	return (i - 1 + n)%n;
}
int prox(int i){
	return (i + 1)%n;
}

int main(){

	fastio;

	cin >> n;
	fr(i, n){
		int x, y;
		cin >> x >> y;
		v.pb({x, y});
	}

	ll xmin, xmax, ymin, ymax;
	ymin = xmin = -1;
	ymax = xmax = 2000;

	fr(i, n){
		point p[4];
		p[0] = v[ant(i)];
		p[1] = v[i];
		p[2] = v[prox(i)];
		p[3] = v[prox(prox(i))];

		//dbg(((p[1] - p[0]) ^ (p[2] - p[1])));
		//dbg(((p[2] - p[1]) ^ (p[3] - p[2])));

		if(((p[1] - p[0]) ^ (p[2] - p[1])) > 0){
			if(((p[2] - p[1]) ^ (p[3] - p[2])) > 0){
				//dbg(p[1].x); dbg(p[2].x);
				if(p[1].y == p[2].y){
					if(p[0].y > p[1].y){
						//olar;
						ymax = min(ymax, p[1].y);
					}
					else{
						//dbg(i);
						ymin = max(ymin, p[1].y);
					}
				}
				else{
					if(p[0].x < p[1].x){
						xmin = max(xmin, p[1].x);
					}
					else{
						xmax = min(xmax, p[1].x);
					}
				}
			}
		}
	}

	if(xmin <= xmax && ymin <= ymax){
		cout << "SAFETY" << endl;
	}
	else{
		cout << "DANGER" << endl;
	}

}
