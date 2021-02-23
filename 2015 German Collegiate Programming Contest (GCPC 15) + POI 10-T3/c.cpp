#include "bits/stdc++.h"
using namespace std;

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

using coord = long double;
const long double EPS = 1e-8;

int sign(coord x){return (x > EPS) - (x < EPS); }

struct point{
	coord x,y;
	point(): x(0), y(0){}
	point(coord _x, coord _y): x(_x), y(_y) {}
	inline point operator+(point p){return {x + p.x, y + p.y};}
	inline point operator-(point p){return {x - p.x, y - p.y};}

	inline coord operator*(point p){return x*p.x + y*p.y;}
	inline coord operator^(point p){return x*p.y - y*p.x;}

	inline long double norm(){return hypot(x, y);}

	inline void print(){cout << x << ' ' << y << endl;} 
};

long double a;
int n;
long double area;
point v[110];

bool ok(long double s){
	long double reti = 0;
	fr(i,n){
		int prox = (i + 1)%n;
		int prev = (i + n - 1)%n;
		long double termo = ((v[prox] - v[i])^(v[prev] - v[i]));
		termo /= s*s;
		termo = abs(termo);
		termo /= 2;
		reti += termo;
	}

	if(reti >= (1 - a)*area) return true;
	else return false;

}

int main(){

	fastio;
	cout << setprecision(10) << fixed;
	cin >> a >> n;
	fr(i,n){
		cin >> v[i].x >> v[i].y;
	}

	fr(i,n){
		int prox = (i + 1)%n;
		area += v[i]^v[prox];
	}

	area /= 2;
	if(area < 0) area = -area;

	long double l = 2;
	long double r = 1000;

	long double best = -1;

	frr(i,100){
		long double m = (l + r)/2;

		if(ok(m)){
			l = m;
			best = m;
		}
		else r = m;
	} 

	cout << best << endl;

}
