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
const ll lim = 10000000;

ll f,T, t0;

ll a1,t1,p1;
ll a2,t2,p2;

int main(){

	fastio;

	cin >> f >> T >> t0;

	cin >> a1 >> t1 >> p1;
	cin >> a2 >> t2 >> p2;

	if(t1 > t2){
		swap(a1,a2);
		swap(t1,t2);
		swap(p1,p2);
	}

	if(t1 >= t0){
		if(f*t0 <= T) cout << 0 << endl;
		else cout << -1 << endl;
		return 0;
	}

	if(t2 >= t0){
		for(int i = 0; i <= lim; i++){
			if(i*a1 >= f){
				if(t1*f <= T){
					cout << i*p1 << endl;
				}
				else{
					cout << -1 << endl;
				}
				return 0;
			}
			else{
				if(i*a1*t1 + (f - i*a1)*t0 <= T){
					cout << i*p1 << endl;
					return 0;
				}
			}
		}
		cout << -1 << endl;
		return 0;
	}

	ll ans = llINF;
	for(int c1 = 0; c1 <= lim; c1++){
		if(c1*a1 >= f){
			if(f*t1 <= T) ans = min(ans, c1*p1);
			continue;
		}
		ll fl = f - c1*a1;
		ll Tl = T - c1*a1*t1;
		if(Tl < 0) continue;

		ll price = c1*p1;

		ll l = 0;
		ll r = lim;

		while(l <= r){
			ll m = (l + r)/2;

			bool ok = false;

			if(m*a2 >= fl){
				if(fl*t2 <= Tl){
					ans = min(ans, price + m*p2);
					ok = true;
				}
			}
			else{
				if(m*a2*t2 + (fl - a2*m)*t0 <= Tl){
					ans = min(ans,price + m*p2);
					ok = true;
				}
			}

			if(ok) r = m - 1;
			else l = m + 1;
		}
	}

	if(ans == llINF) ans = -1;
	cout << ans << endl;


}