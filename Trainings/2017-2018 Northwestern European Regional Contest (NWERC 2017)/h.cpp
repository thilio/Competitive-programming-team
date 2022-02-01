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
#define INF 2000000000000000100

ll a, b, c, d;

bool comp(ll x, ll y){
	return x > y;
}

void solve(){
	ll v[4];
	fr(i, 4) cin >> v[i];
	sort(v, v + 3, comp);
	a = v[0], b = v[1], c = v[2], d = v[3];

	ll ans = (a + d)*(a + d) + b*b + c*c + 7*min(a + d, min(b, c));
	fr(x, d + 1){
		if(2*x >= 7) break;
		fr(y, d + 1 - x){
			if(2*x + 2*y >= 7) break;
			ll z = d - x - y;
			//cout << x << " " << y << " " << z << endl;
			ans = max((a + x)*(a + x) + (b + y)*(b + y) + (c + z) * (c + z) + 7*min(a + x, min(b + y, c + z)), ans);
		}
	}
	cout << ans << endl;

}

signed main(){
	fastio;
	ll t;
	cin >> t;
	while(t--) solve();
}
