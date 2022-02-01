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

ll n,k;
vector<ll> v;

ll buy(ll val){
	ll can = 0;
	fr(i,n){
		ll p = val - v[i];
		
		auto it = upper_bound(all(v),p);
		int pos = it - v.begin();
		pos--;

		if(pos <= i) continue;
		can += pos - i;
	}
	return can;
}

int main(){

	fastio;
	cin >> n >> k;

	fr(i,n){
		ll x;
		cin >> x;
		v.pb(x);
	}

	sort(all(v));

	ll l = 0;
	ll r = 2*MOD;
	ll best = -1;

	while(l <= r){
		ll m = (l + r)/2;
		ll x = buy(m);
		if(x >= k){
			r = m - 1;
			best = m;
		}
		if(x < k){
			l = m + 1;
		}
	}

	cout << best << endl;

}
