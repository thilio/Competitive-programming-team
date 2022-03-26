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

vector<array<double, 3>> pos, neg;

int n;

double eval(array<double, 3> par, double x){
	return par[0]*x*x + par[1]*x + par[2];
}

double up(double x){
	double mn = eval(neg[0], x);
	for(auto y: neg){
		mn = min(mn, eval(y, x));
	}
	return mn;
}

double low(double x){
	double mx = eval(pos[0], x);
	for(auto y: pos){
		mx = max(mx, eval(y, x));
	}
	return mx;
}

int main(){

	fastio;

	cout << setprecision(15) << fixed;

	int n;
	cin >> n;


	fr(i, n){
		int a, b, c;
		cin >> a >> b >> c;

		if(a > 0) pos.pb({(double)a, (double)b, (double)c});
		else neg.pb({(double)a, (double)b, (double)c});
	}

	if(pos.empty()){
		cout << 0 << ' ' << - 1e9 - 1 << endl;
	}
	else if(neg.empty()){
		cout << 0 << ' ' << 1e9 + 1 << endl;
 	}
 	else{
 		double l = -1e9;
 		double r = 1e9;

 		fr(i, 1000){
 		//	dbg(l); dbg(r);
 			double m1 = l + (r - l)/3;
 			double m2 = r - (r - l)/3;

 			double v1 = up(m1) - low(m1);
 			double v2 = up(m2) - low(m2);

 			if(v1 > v2)
 				r = m2;
 			else
 				l = m1;

 		}

 		double p = (l + r)/2;

 		cout << p << ' ' << (up(p) + low(p))/2 << endl;

 	}
}
