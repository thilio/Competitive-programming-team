#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(ll i = 0; i < n; i++)
#define frr(i, n) for(ll i = 1; i <= n; i++)
#define frm(i, n) for(ll i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<ll,ll> pii;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));
#define db cout << "Debug" << endl;
#define all(x) begin(x), end(x)
#define dbg(x)  cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define random mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define myrand(a, b) uniform_ll_distribution<ll>(a, b)(rng)

#define mp make_pair
#define pq priority_queue

#define MAXN 100010
#define MOD 998244353
#define INF 2000000000000000100

bool np[MAXN];
vector<ll> p;

void sieve(){
	for(ll i = 2; i < MAXN; i++){
		if(!np[i]){
			for(ll j = i; j < MAXN; j += i){
				np[j] = true;
			}
			p.pb(i);
		}
	}
}

ll phi(ll n){
	ll j = 0, ans = 1;
	while(p[j] * p[j] <= n){
		ll e = 0, part = 1;
		while(n % p[j] == 0){
			e++;
			n /= p[j];
			part *= p[j];
		}
		if(e)ans = ans * part / p[j] * (p[j] - 1);
		j++;
	}
	if(n > 1){
		ans = ans * (n - 1);
	}
	return ans;
}

ll fastxp(ll n, ll e){
    ll ans = 1, pwr = n;
    while(e){
        if(e%2)  ans = ans * pwr % MOD;
        e /= 2;
        pwr = pwr * pwr % MOD;
    }
    return ans % MOD;
}

ll fac(ll n, ll k){
	ll den = 1, num = 1;
	frr(i, k) {
		den = den * i % MOD;		
		num = num * n % MOD;
		n--;
	}

	return num * fastxp(den, MOD - 2) % MOD;
}

signed main(){
	fastio;
	sieve();
	ll n, k;
	cin >> n >> k;
	cout << phi(n) * fac(n - 1, k - 1) % MOD << endl;
}
