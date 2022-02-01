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

ll dp[MAXN];
ll n;
ll a[MAXN];

ll solve(ll v){
	if(v == 1) return a[1];
	else if(v == 2) return a[2];
	else if(v == 3) {
		return a[1] + a[2] + a[3];
	}
	else if(dp[v] > -1) return dp[v];

	ll ans = solve(v - 1) + a[1] + a[v];
	ans = min(ans, solve(v - 2) + a[v] + 2*a[2] + a[1]);
	return dp[v] = ans;
}

int main(){
	fastio;
	cin >> n;
	mem(dp, -1);
	frr(i, n) cin >> a[i];
	sort(a + 1, a + n + 1);

	cout << solve(n) << endl;
}
