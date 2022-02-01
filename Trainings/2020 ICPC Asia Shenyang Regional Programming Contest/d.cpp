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

vector<pair<vector<ll>, ll>> ans;

void prll_vec(ll ind){
	for(ll i = 0; i < ans[ind].f.size(); i++){
		for(ll j = 0; j < (ans[ind].f)[i] - 1; j++){
			cout<< 'b';
		}
		if(i == ans[ind].f.size() - 1 && ans[ind].s) cout << 'b';
		else cout << 'r';
	}
	cout <<'\n';
}

ll val;
void prll_ans(){
	cout << val << '\n';
	fr(i, ans.size())prll_vec(i);
	exit (0);
}


vector<ll> davez;
void backtracking(ll a, ll b, ll resto){
	if(a + resto + 	2 < b) return;
	if(resto == 0){
		if((a + 1) * b == val){		
			ans.pb({davez, 0});
			if(ans.size() == 100) prll_ans();
		}
		return;
	}

	if((a + resto + 1) * (b) == val){
		davez.pb(resto);
		ans.pb({davez, 1});
		// cout << (a + resto) << " " << b<< endl;

		// for(auto x: davez) cout << x  << " ";
		// cout<< endl;
		if(ans.size() == 100) prll_ans();
		davez.pop_back();
	}

	for(ll i = min((b + resto - a)/2 + 1, resto)/*resto*/; i >= 1; i--){
		davez.pb(i);
		backtracking(b, a + i, resto - i);
		davez.pop_back();
	}
}


ll n;
signed main(){
	fastio;
	cin >> n;
	if(n%2 == 0) val = n/2 * (n + 2)/2;
	else val = (n + 1) * (n + 1) / 4;


	backtracking(0, 0, n);
	prll_ans();
}