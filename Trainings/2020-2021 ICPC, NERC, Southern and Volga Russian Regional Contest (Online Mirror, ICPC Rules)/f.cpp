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

map<pair<pll,bool>, ll> m;

int main(){

	fastio;

	int T;
	cin >> T;
	while(T--){
		m.clear();
		int n;
		cin >> n;

		ll x,y,u,v;
		fr(i,n){
			cin >> x >> y >> u >> v;
			
			ll dx = u - x;
			ll dy = v - y;

			bool ok;

			if(dy == 0){
				dx = 1;
				if(u - x > 0) ok = true;
				else ok = false;
			}
			else if(dx == 0){
				dy = 1;
				if(v - y > 0) ok = true;
				else ok = false;
			}
			else if(dx*dy > 0){
				dx = abs(dx);
				dy = abs(dy);
				ll g = __gcd(dx,dy);
				dx /= g;
				dy /= g;
				if(u - x > 0) ok = true;
				else ok = false;
			}
			else{
				dx = abs(dx);
				dy = abs(dy);
				ll g = __gcd(dx,dy);
				dx /= g;
				dy /= g;
				dx = -dx;
				if(u - x > 0) ok = true;
				else ok = false;	
			}
			

			m[mp(mp(dy,dx),ok)]++;
		}

		ll ans = 0;

		for(auto x: m){
			if(x.fst.snd == false) continue;
			ll term = x.snd;
			pair<pll,bool> at = x.fst;
			at.snd = false;
			ans += term*m[at];
		}

		cout << ans << endl;
		
	}

}
