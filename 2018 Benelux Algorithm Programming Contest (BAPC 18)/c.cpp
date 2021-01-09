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
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

vector<ll> divi;

void divisor(ll n){
	for (ll i = 1; i * i <= n; i++){
		if (n % i == 0){
			divi.pb(i);
			if (i != n/i)
				divi.pb(n/i);
		}
	}
}

int32_t main(){
	fastio;

	ll n;
	cin>>n;

	divisor(n);

	ll ans = llINF;
	ll x, y, z;

	for (int i = 0; i < divi.size(); i++)
		for (int j = 0; j < divi.size(); j++){
			x = divi[i];
			y = divi[j];
			if (n % (x * y) == 0){
				ll z = n / (x * y);
				ans = min(ans, 2 * (x * y + y * z + z * x));
			}
		}

	cout<<ans<<endl;	
}