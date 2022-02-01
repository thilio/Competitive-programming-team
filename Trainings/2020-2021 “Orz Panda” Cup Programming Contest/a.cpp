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

ll w[MAXN], sz[MAXN], pai[MAXN], ap[MAXN], tot[MAXN];
ll n;
ll h[MAXN];

ll find(ll x){
	if(pai[x] == x) return x;
	else return pai[x] = find(pai[x]);
}

void join(ll a, ll b){
	if(ap[a] == 0 || ap[b] == 0) return ;
	a = find(a);
	b = find(b);

	if(a == b) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	pai[b] = a;
	tot[a] += tot[b];
}

int main(){
	fastio;

	cin >> n;
	vector<pii> ord;

	frr(i, n) {
		cin >> h[i] >> w[i];
		pai[i] = i;
		sz[i] = 1;
		tot[i] = w[i];
		ord.pb({-h[i], i});
	}

	sort(ord.begin(), ord.end());
	ll ans = 0;
	for(auto x: ord){
		ap[x.s] = 1;
		join(x.s, x.s + 1);
		join(x.s, x.s - 1);
		ans = max(ans, -x.f*tot[find(x.s)]);
	}

	cout << ans << endl;
}
