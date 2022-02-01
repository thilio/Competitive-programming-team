#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define frm(i, n) for(int i = n-1; i >= 0; i--)

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
#define myrand(a, b) uniform_int_distribution<int>(a, b)(rng)

#define mp make_pair
#define pq priority_queue

#define MAXN 510
#define MAXC 10010
#define MOD 1000000007
#define INF 2000000000000000100

int dp[MAXN][MAXC];
int pai[MAXN][MAXC];
int n, c;
int s[MAXN], d[MAXN];

signed main(){
	fastio;
	cin >> n >> c;
	vector<pii> a, a2;
	frr(i, n){
		cin >> d[i] >> s[i];
		if(d[i] > s[i]) a.pb({s[i] - d[i], i});
		else a2.pb({s[i], i});
	}
	sort(all(a));
	for(auto x: a2) a.pb(x);

	int ind = 0;
	for(auto x : a){
		ind++;
		int j = x.s;

		fr(i, c + 1) {
			pai[ind][i] = 0;
			dp[ind][i] = dp[ind-1][i];	
		}

		frm(i, c + 1){
			if(d[j] + i <= c && s[j] + i <= c && dp[ind][s[j] + i] < dp[ind][i] + 1){
				dp[ind][s[j] + i] = dp[ind][i] + 1;
				pai[ind][s[j] + i] = 1;
			}
		}
	}

	int ans = 0;
	frr(i, c) {
		if(dp[ind][i] > dp[ind][ans]){
			ans = i;
		}
	}
	cout << dp[ind][ans] << endl;
	vector<int> apps;

	for(int i = ind; i > 0; i--){
		if(pai[i][ans]) {
			ans -= s[a[i-1].s];
			apps.pb(a[i-1].s);
		}
	}
	//if(dp[ind][ans] != (int)apps.size()) assert(0);
	frm(x, (int)apps.size()) cout << apps[x] << " ";
	cout << endl;
}
