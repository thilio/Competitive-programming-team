#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(long long int i=0;i<n;i++)
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

ll fat[3000];

ll fexp(ll base,ll exp){
	if(exp == 0) return 1ll;
	ll ans = fexp(base,exp/2);
	ans = ans*ans;
	ans %= MOD;
	if(exp&1) ans *= base;
	ans%= MOD;
	return ans;
}

ll invmod(ll x){
	return fexp(x,MOD - 2);
}

void init(){
	fat[0] = 1;
	frr(i,2502){
		fat[i] = i*fat[i-1];
		fat[i] %= MOD;
	}
}

ll f(ll j){
	ll term = 1;
	term = fat[k];
	term*= invmod(fat[j]);
	term%=MOD;
	term*= invmod(fat[k-j]);
	term%=MOD;
	///dbg(term);
	term*= k- j;
	term%= MOD;
	term *= fexp(k-j-1,n-1);
	term %= MOD;

	return term;

}

int main(){

	fastio;
	cin >> n >> k;

	init();

	ll ans = 0;
	fr(j,k){
		ans += fexp(-1,j)*f(j);

		ans += MOD;
		ans %= MOD;
		//dbg(ans);
	}

	cout << ans << endl;
}
