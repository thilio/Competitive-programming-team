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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e7 + 10;

const ll mod = 1e9 + 7;

ll fat[MAXN];

ll fastxp(ll base, ll exp){
	ll ans = 1;
	while (exp){
		if (exp & 1)
			ans = (ans * base) % mod;
		base = (base * base) % mod;
		exp >>= 1;
	}

	return ans;
}

ll invmod(ll x){
	return fastxp(x, mod - 2);
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int T;
	cin>>T;

	fat[0] = 1;

	for (ll i = 1; i < MAXN; i++)
		fat[i] = (fat[i - 1] * i) % mod;


	ll n, m, k;
	while (T--){
		cin>>n>>m>>k;

		if (k > n){
			cout<<0<<endl;
			continue;
		}

		ll ans = fastxp(m, k);
		ll aux = (fat[n] * invmod(fat[k])) % mod;
		aux = (aux * invmod(fat[n - k])) % mod;

		ans = (ans * aux) % mod;

		cout<<ans<<endl;
	}

}