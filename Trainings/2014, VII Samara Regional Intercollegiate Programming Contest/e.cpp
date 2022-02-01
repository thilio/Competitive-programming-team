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

ll n, m;
ll l[MAXN], r[MAXN];
ll a[MAXN];

void solve(ll i){
	if(l[i - 1] == -1 || r[i + 1] == -1){
		cout << "Never" << endl;
		return;
	}
	ll periodo = l[i - 1] * r[i + 1] / __gcd(l[i - 1], r[i + 1]);
	if(periodo % a[i] == 0){
		cout << "Never" << endl;
		return;
	}

	ll q = (m - 1) / periodo + 1;
	ll val = q * periodo;
	if(val % a[i] == 0) val += periodo;

	val -= m;
	if(val > 1000000000){
		cout << "Never" << endl;
		return;
	}
	cout << val << endl;
}

signed main(){
	fastio;
	cin >> n >> m;
	frr(i, n) cin >> a[i];
	l[0] = 1;
	frr(i, n) {
		l[i] = l[i - 1] * a[i] / __gcd(l[i - 1], a[i]);
		if(l[i] >= 2 * MOD) l[i] = -1;
		if(l[i - 1] == -1) l[i] = -1;
	}

	r[n + 1] = 1;
	for(ll i = n; i >= 1; i--) {
		r[i] = r[i + 1] * a[i] / __gcd(r[i + 1], a[i]);
		if(r[i] >= 2 * MOD) r[i] = -1;
		if(r[i + 1] == -1) r[i] = -1;
	}

	frr(i, n) solve(i);
}
