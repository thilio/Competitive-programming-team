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
#define INF 2000000000000000100

vector<int> a, b;
int n;

int d[MAXN], t[MAXN];

int solve(int x, int y){
	int itx = lower_bound(all(a), x + 1) - a.begin();
	int ity = lower_bound(all(b), y + 1) - b.begin();
	if(itx > ity) return 1;
	else if(itx < ity) return -1;
	else return 0;
}

signed main(){
	fastio;
	cin >> n;
	a.pb(0), b.pb(0);
	fr(i, n){
		int x;
		cin >> x;
		a.pb(max(x, a.back()));
	}
	fr(i, n){
		int x;
		cin >> x;
		b.pb(max(x, b.back()));
	}
	int m;
	cin >> m;
	fr(i, m) cin >> d[i];
	fr(i, m) cin >> t[i];
	fr(i, m){
		int aux = solve(d[i], t[i]);
		if(aux == 1) cout << "Constantine" << '\n';
		else if(aux == -1) cout << "Mike" << '\n';
		else cout << "Draw" << '\n';
	}
}
