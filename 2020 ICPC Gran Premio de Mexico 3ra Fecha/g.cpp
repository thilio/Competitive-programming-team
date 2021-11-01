#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define endl '\n'
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

int g[100100], a[100100], b[100100];
int n;

int seg[500500];
int dp[100100];

void update(int node, int l, int r, int pos, int val){
	if(pos < l || pos > r) return;
	if(l == r){
		seg[node] = val;
		return; 
	}

	int m = (l + r)/2;
	update(2*node, l, m, pos, val);
	update(2*node + 1, m + 1, r, pos, val);

	seg[node] = max(seg[2*node], seg[2*node + 1]);
}

int query(int node, int l, int r, int a, int b){
	if(b < l || a > r) return 0;
	if(a <= l && r <= b) return seg[node];

	int m = (l + r)/2;
	int q1 = query(2*node, l, m, a, b);
	int q2 = query(2*node + 1,m + 1, r, a, b);

	return max(q1, q2);
}

int main(){

	fastio;
	cin >> n;

	frr(i, n) cin >> g[i] >> a[i] >> b[i];

	for(int i = n; i > 0; i--){
		if(i + a[i] > n){
			dp[i] = g[i];
		}
		else{
			dp[i] = g[i] + query(1, 1, n, i + a[i], min(i + b[i], n));
		}
		update(1, 1, n, i, dp[i]);
	}

	int ans = 0;

	frr(i, n) ans = max(ans, dp[i]);

	cout << ans << endl;

}
