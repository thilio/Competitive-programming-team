#include "bits/stdc++.h"
using namespace std;

using coord = long long int;
const long double EPS = 1e-8;

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

int sign(coord x){ return (x > EPS) - (x < -EPS);}

struct point {
	coord x,y;
	point(): x(0),y(0){} point(coord _x, coord _y): x(_x), y(_y) {}
	inline point operator+(point p){return {x + p.x, y + p.y}; }
	inline point operator-(point p){return {x - p.x, y - p.y}; }

	inline coord operator^(point p){return x*p.y - y*p.x;}
	inline void operator= (point p){x = p.x;y = p.y;}
	inline void print() {cout << x << ' ' << y << '\n';}
};

point v[5000];
ll g[5000];
point ori;
int n;

bool comp(int a,int b){
	point pa = v[a] - ori;
	point pb = v[b] - ori;

	ll cross = (pa^pb);
	return (cross > 0);
}

ll go(ll ind){
	ori = v[ind];

	vector<int> up;
	vector<int> down;

	frr(i,n){
		if(i == ind) continue;
		if(v[i].y != ori.y){
			if(v[i].y > ori.y) up.pb(i);
			else down.pb(i);
		}
		else{
			if(v[i].x > ori.x) up.pb(i);
			else down.pb(i);
		}
	}

	sort(all(up),comp);
	sort(all(down),comp);

	ll val_up = 0;
	ll val_down = 0;

	for(auto x: up) val_up += g[x];
	for(auto x: down) val_down += g[x];

	int p = 0;
	int q = 0;

	ll dif = llINF;

	while(p < up.size() || q < down.size()){
		if(p == up.size()){
			int at = down[q];
			q++;
			val_down -= g[at];
			dif = min(dif, abs(val_up - val_down));
			val_up += g[at];
		}
		else if(q == down.size()){
			int at = up[p];
			p++;
			val_up -= g[at];
			dif = min(dif, abs(val_up - val_down));
			val_down += g[at];
		}
		else{
			if(((v[up[p]] - ori)^(v[down[q]] - ori)) > 0){
				int at = down[q];
				q++;
				val_down -= g[at];
				dif = min(dif, abs(val_up - val_down));
				val_up += g[at];
			}
			else{
				int at = up[p];
				p++;
				val_up -= g[at];
				dif = min(dif, abs(val_up - val_down));
				val_down += g[at];
			}
		}
	}
	return dif;
}

int main(){

	fastio;

	cin >> n;
	frr(i,n){
		cin >> v[i].x >> v[i].y >> g[i];
	}
	if(n == 2){
		cout << 0 << endl;
		return 0;
	}
	ll ans = llINF;
	frr(i,n){
		ans = min(ans, go(i));
	}

	cout << ans << endl;

}
