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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

using coord = long double;
const long double pi = acos(-1);
const long double EPS = 1e-8;

int signal(coord x) { return (x > EPS) - (x < -EPS); }
coord sq(coord x) { return x * x; }

struct point {
	coord x, y, z;
	point(coord _x, coord _y, coord _z): x(_x), y(_y), z(_z) {}
	inline point operator+(point& o){ return {x + o.x, y + o.y, z + o.z}; }
	inline point operator-(point& o){ return {x - o.x, y - o.y, z - o.z}; }
	inline point operator*(coord o){ return {x * o, y * o, z * o}; }
	inline point operator/(coord o){ return {x / o, y / o, z / o}; }
	inline void operator=(point o){ x = o.x, y = o.y, z = o.z; }
	inline bool operator==(point& o){return signal(x - o.x) == 0 and signal(y - o.y) == 0 
		and signal(z - o.z) == 0; }

	inline coord operator*(point& o){ return x * o.x + y * o.y - z * o.z; }
	//inline coord operator^(point & o){ return x * o.y - y * o.x; }

	inline long double norm(){ return sqrt(x * x + y * y + z * z); }
	inline coord norm2(){ return x * x + y * y + z * z; }

	void print(){ cout<<x<<' '<<y<<' '<<z<<'\n'; }
};

// roda o vetor t ao redor do vetor u com angulo ang
point rot_vec(point t, point u, coord ang){
	long double coss = cos(ang);
	long double senn = sin(ang);

	long double R[3][3];
	R[0][0] = coss + u.x * u.x * (1 - coss);
	R[0][1] = -u.z * senn + u.x * u.y * (1 - coss);
	R[0][2] = u.y * senn + u.x * u.z * (1 - coss);
	R[1][0] = u.z * senn + u.x * u.y * (1 - coss);
	R[1][1] = coss + u.y * u.y * (1 - coss);
	R[1][2] = -u.x * senn + u.y * u.z * (1 - coss);
	R[2][0] = -u.y * senn + u.z * u.x * (1 - coss);
	R[2][1] = u.x * senn + u.z * u.y * (1 - coss);
	R[2][2] = coss + u.z *u.z * (1 - coss);

	return point(
		t.x*R[0][0] + t.y*R[0][1] + t.z*R[0][2],
		t.x*R[1][0] + t.y*R[1][1] + t.z*R[1][2],
		t.x*R[2][0] + t.y*R[2][1] + t.z*R[2][2]);
}

void solve(){
	long double x, y, z, l, h;

	cin>>x>>y>>z;
	point n = point(x, y, z);
	cin>>x>>y>>z;
	point a = point(x, y, z);

	cin>>l>>h;

	n = n/n.norm();

	point b = rot_vec(a, n, (2*pi)/3);
	point c = rot_vec(b, n, (2*pi)/3);
	point base = point(0, 0, -h);

	cout<<(a - base).norm()<<' '<<(b - base).norm()<<' '<<(c - base).norm()<<endl;
}

int32_t main(){
	freopen("jupiter.in", "r", stdin);
	fastio;
	cout << setprecision(6)<<fixed;

	int T;
	cin>>T;
	while (T--)
		solve();
}