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

#define MAXN 1000010
#define MOD 1000000007
#define INF 2000000000000000100

map<pii, set<int>> m;
int a[MAXN];
int p[MAXN];
int n;

signed main(){
	fastio;
	cin >> n;
	fr(i, n) cin >> a[i], p[i] = a[i];
	fr(i, n-1){
		m[{a[i], a[i+1]}].insert(i);
	}
	sort(a, a + n);
	int ans = n - 1;
	fr(i, n-1){
		int tam = m[{a[i], a[i+1]}].size(); 
		if(tam){
			ans--;
			if(a[i] < a[i + 1] && a[i + 1] == a[i + 2] && tam == 1){
				int j = *(m[{a[i], a[i + 1]}].begin());

				if(m[{p[j + 1], p[j + 2]}].size()){
					m[{p[j + 1], p[j + 2]}].erase(j + 1);
				}
			}
			m[{a[i], a[i+1]}].erase(m[{a[i], a[i+1]}].begin());
		}
	}
	cout << ans << endl;
}