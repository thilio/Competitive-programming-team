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

vector<pll> v;

int main(){

	fastio;

	ll n,m;
	cin >> n >> m;

	for(ll i = 2; i*i <= m; i++){
		ll ct = 0;
		while(m%i == 0){
			m /= i;
			ct++;
		}
		v.pb(mp(i,ct));
	}
	if(m != 1){
		v.pb(mp(m,1));
	}

	ll ans = 1;

	for(auto x: v){
		while(x.snd/n > 0){
			ans *= x.fst;
			x.snd -= n;
		}
	}

	cout << ans << endl;

}
