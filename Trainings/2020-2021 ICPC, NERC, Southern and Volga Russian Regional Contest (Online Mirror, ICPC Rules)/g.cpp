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

using coord = double;
const long double EPS = 1e-8;

int sign(coord x){return (x > -EPS) - (x < EPS);}
coord sq(coord x){return x*x; }

struct point {
	coord x,y;
	point(): x(0),y (0) {} point(coord _x, coord _y): x(_x), y(_y) {}
	inline point operator+ (point p){ return {x + p.x, y + p.y}; }
	inline point operator- (point p){ return {x - p.x, y - p.y}; }
	inline void operator=  (point p){x = p.x; y = p.y;}
	inline bool operator== (point p){ return (sign(x - p.x) == 0 && sign(y -p.y) == 0);}

	inline point rot90(){return {-y,x}; }
	inline coord norm(){return sqrt(x*x + y*y);}
	inline coord norm2(){return (x*x + y*y);}

	inline coord operator* (point p){return x*p.x + y*p.y;}
	inline coord operator^ (point p){return x*p.y - y*p.x;}

	inline bool operator<(point p) const { return sign(x - p.x) != 0 ? sign(x - p.x) < 0 : sign(y - p.y) < 0; } // lex_sort
	inline void print(){cout << x << ' ' << y << endl;}
};

struct line{
	point p; coord c;
	line() {} line(point _p, coord _c): p(_p), c(_c) {}
	line (point a,point b): p((b - a).rot90()), c(p*a){}
	bool paral(line r) {return sign(r.p^p) == 0;}
	void get_intsec(line l, point &x){
		coord d = p^l.p;
		x = {(c*l.p.y - l.c*p.y)/d, (p.x*l.c - c*l.p.x)/d};
	}
};

int n,h;
point ori;
point v[200200];
bool vis[200200];
int mn;

int main(){

	//fastio;

	scanf("%d %d", &n, &h);

	fr(i,n){
		scanf("%lf %lf", &v[i].x, &v[i].y);
	}

	ori = v[n - 1];
	ori.y += h;

	vis[n - 1] = true;
	mn = n - 1;

	coord ans = 0.0;

	for(int i = n - 2; i>= 0; i--){
		if(((v[i] - ori)^(v[mn] - ori)) >= 0){
			vis[i] = true;
		}
		else{
			vis[i] = false;
		}
		
		if(vis[i] == false) continue;
		if(vis[i+1] == true){
			ans += sqrt((v[i + 1] - v[i])*(v[i + 1] - v[i]));
		}
		else{
			line l = {v[i], v[i + 1]};
			line r = {ori, v[mn]};
			point x;
			l.get_intsec(r,x);
			ans += sqrt((v[i] - x)*(v[i] - x));
		}
		mn = i;
			

	}
	

	printf("%.10lf\n", ans);


}
