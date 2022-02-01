#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 2e5 + 10;

ll n;

struct seg{
	ll t[2 * MAXN];

	void init(){ memset(t, 0, sizeof t); }

	void modfy(int p, ll value) {  // set value at position p
	  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
	}

	ll query(int l, int r) {  // sum on interval [l, r)
	  ll res = 0;
	  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
	    if (l&1) res += t[l++];
	    if (r&1) res += t[--r];
	  }
	  return res;
	}
};

vector<pair<ll,ll>> v;

seg freq[2], sum[2];

int32_t main(){	
	fastio;
	freq[0].init(), freq[1].init(), sum[0].init(), sum[1].init();

	ll k;

	cin>>n>>k;

	ll x;
	fr(i, n){
		cin>>x;
		v.pb({x, i});
	}

	sort(all(v));

	ll ans = 0, aux, l, r, pos, val;
	for (auto x : v){
		pos = x.snd, val = x.fst;

		l = max(pos - k + 1, k - pos - 1);
		r = min(pos + k, 2 * n - k - pos);

		
		ans -= sum[(k + 1 + x.snd) % 2].query(l, r + 1);
		aux = freq[(k + 1 + x.snd) % 2].query(l, r + 1);
		ans += aux * x.fst;

		sum[x.snd % 2].modfy(x.snd, x.fst);
		freq[x.snd % 2].modfy(x.snd, 1);
	}

	cout<<ans<<endl;
}
