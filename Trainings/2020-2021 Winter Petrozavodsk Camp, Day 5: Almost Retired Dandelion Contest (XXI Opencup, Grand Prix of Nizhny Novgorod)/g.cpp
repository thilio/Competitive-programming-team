#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(ll i = 0; i < n; i++)
#define frr(i, n) for(ll i = 1; i <= n; i++)
#define frm(i, n) for(ll i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));
#define db cout << "Debug" << endl;
#define all(x) begin(x), end(x)
#define dbg(x)  cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define random mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define myrand(a, b) uniform_int_distribution<ll>(a, b)(rng)

#define mp make_pair
#define pq priority_queue

#define MAXN 100010
#define MOD 1000000007
#define INF 2000000000000000100

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

namespace randNT{
    random;
	typedef long long int u64;
	u64 modmul(u64 a, u64 b, u64 M) {
		ll ret = a * b - M * u64(1.L / M * a * b);
		return ret + M * (ret < 0) - M * (ret >= (ll)M);
	}
    u64 modpow(u64 b, u64 e, u64 mod) {
        u64 ans = 1;
        for (; e; b = modmul(b, b, mod), e /= 2)
            if (e & 1) ans = modmul(ans, b, mod);
        return ans;
    }

    bool isPrime(u64 n, int iter = 5){
        if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
        u64 s = __builtin_ctzll((ll)n-1), d = n >> s, a = 2;
        while (iter--) {
            u64 p = modpow(a%n, d, n), i = s;
            while (p != 1 && p != n - 1 && a % n && i--)
                p = modmul(p, p, n);
            if (p != n-1 && i != s) return 0;
            a = 2 + myrand(0, n - 4);
        }
        return 1;
    }

    u64 rho(u64 n) {
        if(n % 2 == 0) return 2;
        u64 d, c = myrand(1, n), x = myrand(1, n), y = x, iter = 10;
        auto f = [n, c](u64 x) { return modmul(x, x, n) + c; };
        do {
            x = f(x), y = f(f(y));
            d = __gcd(abs(x - y), n);
        } while (d == 1 && iter--);
        return d;
    }

    u64 pollard(u64 n) {
		auto f = [n](u64 x) { return modmul(x, x, n) + 1; };
		u64 x = 0, y = 0, t = 30, prd = 2, q;
		while (t++ % 40 || __gcd(prd, n) == 1) {
			if (x == y) y = f(x);
			if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
			x = f(x), y = f(f(y));
		}
		return __gcd(prd, n);
	}

    vector<u64> factor(u64 n) {
        if (n == 1) return {};
        if (isPrime(n)) return {n};
        u64 x = pollard(n);
        auto l = factor(x), r = factor(n / x);
        l.insert(l.end(), all(r));
        return l;
    }
};  

vector<map<ll, ll>> p;

void decompose(ll n){
	map<ll, ll> m;
	vector<ll> f = randNT::factor(n);
	for(auto x: f) m[x]++;
	// cout << n << endl;
	// for(auto x: F) cout << x.f << " " << x.s << endl;
	p.pb(m);
}

vector<ll> segments;
ll n;
void build(ll ind){
	for(auto & x: p[ind]){
		if(x.s){
			ll j = ind + 1;
			while(j < n && p[j][x.f]){
				p[j][x.f] = 0;
				j++;
			}
			segments.pb(j - ind);
			x.s = 0;
		}
	}
}

ll nim[MAXN];

signed main(){
	fastio;
	cin >> n;
	//n = 1000;
	fr(i, n){
		ll a;
		//a = 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19;
		cin >> a;
		decompose(a);
	}
	fr(i, n) build(i);
	//for(auto x: segments) dbg(x);
	map<ll, ll> mex;
	mex[0] = 1;
	frr(i, n){
		fr(j, i){
			mex[nim[j]^nim[i - 1 - j]] = 1;
		}
		while(mex[nim[i]] == 1){
			nim[i]++;
		}
	}
	//frr(i, n) cout << nim[i] << endl;
	ll x = 0;
	for(auto i: segments) x ^= nim[i];
	
	if(x) cout << "First" << endl;
	else cout << "Second" << endl;
}
