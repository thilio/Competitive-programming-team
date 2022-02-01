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
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

ll llrand() { ll a = rand(); a<<= 32; a+= rand(); return a;}
ll mul_mod(ll a, ll b, ll mod) {
    return (__int128)a * b % mod;
}

ll fastxp(ll b, ll e, ll mod){
    if(e == 0) return 1;
    ll ans = fastxp(b, e/2, mod);

    ans = (ans*ans)%mod;

    if(b%2 == 1) ans *= b;

    return (ans)%mod;
}

using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n, int iter=5) { // returns true if n is probably prime, else returns false.
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}

ll rho(ll n) {
	ll d, c = rand() % n, x = rand() % n, xx = x;
	ll lim = 100000;
	if (n % 2 == 0)
		return 2;
	do {
		x = (mul_mod(x, x, n) + c) % n;
		xx = (mul_mod(xx, xx, n) + c) % n;
		xx = (mul_mod(xx, xx, n) + c) % n;
		d = __gcd(abs(x - xx), n);
	} while (d == 1 && lim--);
	return d;
}
map <ll,ll> F;
void factor(ll n) {
	if (n == 1)
		return;
	if (MillerRabin(n)) {
		F[n]++;
		return;
	}
	ll d = rho(n);
	factor(d);
	factor(n/d);
}

int main(){
	fastio;

	ll n;
	ll N;
	cin >> N;
	n = N;

	factor(n);

	ll d = 1;
	for(auto x: F){
		d *= (x.s + 1);
	}

	cout << (ll)d << endl;
}
