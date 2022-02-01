#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define pi acos(-1)

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

int n;
long double tempo;
long double tt;
long double alpha,T;
ll d;

long double ang(long double x,long double y){
	if(x > 0){
		return atan(y/x);
	}
	if(x == 0){
		return pi/2;
	}
	if(x < 0){
		x = -x;
		return pi - atan(y/x);
	}

	return 0;
}

int main(){

	fastio;
	cout << setprecision(12) << fixed;
	cin >> n >> tempo;
	cin >> alpha >> T >> d;

	alpha *= (pi)/180;

	fr(i,n){
		tt = tempo;
		long double x,y;
		cin >> x >> y;

		long double ans = 0;

		if(x*x + y*y > d*d){
			cout << ans << endl;
			continue;
		}

		if(ang(x,y) >= alpha/2){
			long double z = ((ang(x,y) - (alpha/2))/(2*pi))*T;
			if(tt <= z){
				cout << ans << endl;
			}
			else{
				tt -= z;
				long double one_r = (alpha/(2*pi))*T;
				ans += (floor(tt/T))*one_r;
				//dbg(floor(tt/T));
				tt -= floor(tt/T)*T;
				//dbg(ans);
				ans += min(tt,one_r);
				cout << ans << endl;
			}
		}

		else{
			long double pri = (((alpha/2) + ang(x,y))/(2*pi))*T;
			if(pri >= tt){
				cout << tt << endl;
			}
			else{
				ans += pri;
				tt -= pri;
				pri = ((2*pi - alpha)/(2*pi))*T;
				if(pri >= tt){
					cout << ans << endl;
				}
				else{
					tt -= pri;
					long double one_r = (alpha/(2*pi))*T;
					ans += (floor(tt/T))*one_r;

					tt -= floor(tt/T)*T;
					ans += min(tt,one_r);
					cout << ans << endl;
				}
			}
		}

	}


}
