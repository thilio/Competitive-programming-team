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

#define MAXN 100010
#define MOD 1000000007
#define INF 1000000000000000100

void solve(string s, int k){
	int i = 0, ans = 0;
	vector<pair<int, char>> v;
	while(i < s.size()){
		if(s[i] >= 'a' && s[i] <= 'z') {
			v.pb({1, s[i]});
			ans++;
			i++;
			continue;
		}

		int val = 0;
		while(s[i] < 'a' || s[i] > 'z'){
			val *= 10;
			val += s[i] - '0';
			if(val > 1000000) {
				cout << "unfeasible" << endl;
				return;
			}
			i++;
		}
		v.pb({val, s[i]});
		i++;
		ans += val;
	}
	if(ans <= k){
		for(auto x: v){
			fr(i, x.f) cout << x.s;
		}
		cout << endl;
	}
	else{
		cout << "unfeasible" << endl;
	}
}

signed main(){
	fastio;
	int t;
	cin >> t;

	while(t--){
		string s;
		cin >> s;
		int k;
		cin >> k;
		solve(s, k);
	}
}
