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

using coord = long long;
int sign(coord x){ return (x > 0) - (x < 0); }

struct point {
	coord x, y;
	point() : x(0), y(0) {} point(coord _x, coord _y): x(_x), y(_y) {}
	inline point operator+(point p){ return {x + p.x, y + p.y}; }
	inline point operator-(point p){ return {x - p.x, y - p.y}; }
	inline point operator*(coord o){ return {x * o, y * o}; }
	inline void operator=(point p){ x = p.x, y = p.y; }

	inline coord operator*(point p){ return x * p.x + y * p.y; } // |a||b|cos(tht)
	inline coord operator^(point p){ return x * p.y - y * p.x; } // |a||b|sin(tht), this -> p
};

int n;
vector<point> v;

ll area;


ll diferenca(ll now, ll irc){
	ll a = area - now;
	ll b = now;

	ll aa = area - (now + irc);
	ll bb = now + irc;

	return abs(a - b) > abs(aa - bb);
}


ll rotating(){
	int l = 1, r = 2;

	coord now = 0;
	coord ans = 0;

	for (int i = 0; i < n; i++){
		ll irc = abs((v[l] - v[i]) ^ (v[r] - v[i])); // incremento
	
		while (diferenca(now, irc)){ // pode ser mais equilibrado
			now += irc;
			l = r;
			r = (r + 1) % n;

			irc = abs((v[l] - v[i]) ^ (v[r] - v[i]));
		}
	
		ans = max(ans, max(area - now, now));

		now -= abs((v[l] - v[i]) ^ (v[l] - v[i + 1]));
	}

	return ans;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n;

	coord x, y;
	fr(i, n){ // counter clockwise
		cin>>x>>y;
		v.pb(point(x, y));
	}

	for (int i = 1; i < n - 1; i++)
		area += (v[i] - v[0])^(v[i + 1] - v[0]);

	area = abs(area);

	ll ans = rotating();

	cout<<max(area - ans, ans)<<' '<<min(area - ans, ans)<<endl;
}