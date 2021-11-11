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
#define MOD 1000000007
#define INF 1000000000000000100

const ll N = 1<<21;

template <typename T>
struct FWT {
	void fwt(T io[], ll n) {
		for (ll d = 1; d < n; d <<= 1) {
			for (ll i = 0, m = d<<1; i < n; i += m) {
				for (ll j = 0; j < d; j++) { /// Don't forget modulo if required
					T x = io[i+j], y = io[i+j+d];
					io[i+j] = (x+y), io[i+j+d] = (x-y);	// xor
					// io[i+j] = x+y; // and
					// io[i+j+d] = x+y; // or
				}
			}
		}
	}
	void ufwt(T io[], ll n) {
		for (ll d = 1; d < n; d <<= 1) {
			for (ll i = 0, m = d<<1; i < n; i += m) {
				for (ll j = 0; j < d; j++) { /// Don't forget modulo if required
					T x = io[i+j], y = io[i+j+d];
					 /// Modular inverse if required here
					io[i+j] = (x+y)>>1, io[i+j+d] = (x-y)>>1; // xor
					// io[i+j] = x-y; // and
					// io[i+j+d] = y-x; // or
				}
			}
		}
	}
	// a, b are two polynomials and n is size which is power of two
	void convolution(T a[], T b[], ll n) {
		fwt(a, n);
		fwt(b, n);
		for (ll i = 0; i < n; i++)
			a[i] = a[i]*b[i];
		ufwt(a, n);
	}
	// for a*a	
	void self_convolution(T a[], ll n) {
		fwt(a, n);
		for (ll i = 0; i < n; i++)
			a[i] = a[i]*a[i];
		ufwt(a, n);
	}
};
FWT<ll> fwt;

ll m[N];
ll n, q, k;

void read(){
	cin >> n >> q >> k;
	fr(i, n){
		string s;
		cin >> s;
		ll mask = 0;
		fr(j, q) if(s[j] == 'A') mask += (1 << j);
		m[mask]++;
	}
}


signed main(){
	fastio;
	read();
	fwt.self_convolution(m, (1 << q));
	m[0] -= n;
	fr(i, (1 << q)) m[i] /= 2;

	for(int i = 0; i < q; ++i) for(int mask = 0; mask < (1 << q); ++mask){
		if(mask & (1<<i))
			m[mask] += m[mask^(1<<i)];
	}

	ll ans = 0;
	fr(i, (1 << q)){
		if(m[i] <= n*(n-1)/2 - k) ans++;
	}
	cout << ans << endl;
}
