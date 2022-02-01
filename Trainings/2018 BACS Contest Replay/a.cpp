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
ll x,l,n;

pll simp(pll a){
	ll g = __gcd(a.fst, a.snd);
	a.fst /= g;
	a.snd /= g;
	return a;
}

int main(){

	fastio;

	int T;
	cin >> T;
	int caso = 1;
	while(T--){
		cin >> x >> l >> n;
		ll den = n - l + 1;

		ll nom = 0;

		if(l <= x) nom = x - l;

		ll survive = 0;
		
		if(x%2){
			ll sz = (x - 1)/2;
			ll pot = 1;

			while(pot + sz <= n){
				if(pot > sz && pot + sz >= l) survive++;
				pot *= 2;
			}
		}

		pll ans = simp(mp(nom + survive, den));

		cout << "Case "<<caso++<< ": ";
		cout << ans.fst << '/' << ans.snd << endl;

	}

}
