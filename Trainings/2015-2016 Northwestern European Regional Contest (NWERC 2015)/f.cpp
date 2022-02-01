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
const long double pi = acos(-1);
const long double EPS = 1e-8;
const long long raio = 6370;

int sign(coord x) {return (x > EPS) - (x < -EPS);}

struct point {
	coord x,y,z;
	point(): x(0), y(0), z(0) {} 
	point(coord _x, coord _y, coord _z): x(_x), y(_y), z(_z) {}

	inline point operator+(point p){return {x + p.x, y + p.y, z + p.z}; }
	inline point operator-(point p){return {x -  p.x, y -p.y, z - p.z}; }
	inline point operator*(long long s){return {x*s, y*s, z*s}; }
	inline point operator*(long double s){return {x*s, y*s, z*s}; }

	inline coord operator*(point p) {return x*p.x + y*p.y + z*p.z;}
	inline point operator^(point p) {return {y*p.z - z*p.y, z*p.x - x*p.z ,x*p.y - p.x*y };}

	inline coord norm(){return sqrt(x*x + y*y + z*z);}

	//inline int ccw(point p){return sign(*this ^ p);}
	inline bool operator==(point p) {return x == p.x && y == p.y && z == p.z;}
	inline void operator= (point p){x = p.x; y = p.y; z = p.z;}

};

point ori;

point trans(coord lag, coord lng){
	lag *= 2*pi/360;
	lng *= 2*pi/360;
	return {raio*cos(lag)*cos(lng), raio*cos(lag)*sin(lng), raio*sin(lag)};
}

coord dist_es(point a, point b){ // Distancia ao longo da esfera
	coord theta;
	theta = (a*b)/(a.norm()*b.norm());
	theta = acos(theta);
	//dbg(theta);

	return (raio*theta);
}

coord dist_li(point a, point b){
	return (a - b).norm();
}

bool comp(point a, point b){
	return (dist_es(a,ori) < dist_es(b, ori));
}

bool contains (point P, point a, point b){
	if(sign((a^P)*(P^b)) >= 0 && sign((a^P)*(a^b)) >= 0) return true;
	return false;
}

point intersec(point a, point b, point c, point d){
	point N1 = a^b;
	point N2 = c^d;

	point p = N1^N2;

	p = p*(raio/p.norm());

	point P1 = p;
	point P2 = p*(-1ll);

	if(contains(P1,a,b) && contains(P1, c, d)) return P1;
	if(contains(P2,a,b) && contains(P2, c, d)) return P2;
	return{0,0,0};


}

vector<point> continents[33];
int c;
int m;
vector<point> travel;

int main(){

	fastio;

	cout << setprecision(10) << fixed;

 	cin >> c;
	fr(i,c){
		int n;
		cin >> n;
		coord lag; coord lng;
		fr(j,n){
			cin >> lag >> lng;
			continents[i].pb(trans(lag,lng));	
		}	
	}

	cin >> m;
	fr(i,m){
		coord a; coord b;
		cin >> a >> b;
		travel.pb(trans(a,b));
	}

	coord ans = 0.0;

	for(int i = 0; i < m - 1; i++){
		ans += dist_es(travel[i], travel[i + 1]);
	}

	coord agua = 0.0;

	int terra = 1;
	for(int i = 0; i < m - 1; i++){

		point a = travel[i];
		point b = travel[i + 1];

		vector<point> inter;
		inter.clear();

		fr(j, c){
			int sz = continents[j].size();
			for(int k = 0; k < sz - 1; k++){
				point p = intersec(a,b,continents[j][k], continents[j][k + 1]);
				if(sign(p.norm()) >= 1) inter.pb(p);
			}
			
			point p = intersec(a,b,continents[j][sz-1], continents[j][0]);
			if(sign(p.norm()) >= 1) inter.pb(p);
		}


		ori = a;
		sort(all(inter), comp);

		point estou = a;

		for(auto x: inter){
			coord dd = dist_es(estou, x);
			if(terra == 0) agua += dd;
			//dbg(terra)
			terra = 1 - terra;
			estou = x;
		}
		coord dd = dist_es(estou, b);
		if(terra == 0) agua += dd;

	}

	cout << ans << ' ' << 100*agua/ans << endl;
/*
	point aux = intersec(travel[1], travel[2], continents[0][0], continents[0][1]);
	cout << aux.x << " " << aux.y << " " << aux.z << endl;
	cout << travel[1].x << " " << travel[1].y << " " << travel[1].z << endl;
	cout << travel[2].x << " " << travel[2].y << " " << travel[2].z << endl;
	cout << continents[0][0].x << " " << continents[0][0].y << " " << continents[0][0].z << endl;
	cout << continents[0][1].x << " " << continents[0][1].y << " " << continents[0][1].z << endl;
*/
}
