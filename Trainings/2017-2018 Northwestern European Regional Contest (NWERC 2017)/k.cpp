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

int n;
vector<int> in;

long double rat[100100];

long double dp[5000][2];

void solve(int l, int r){
	if(l == r){
		dp[l][1] = 1;
		return;
	}
	int m = (l + r)/2;
	solve(l, m); solve(m + 1, r);

	for(int i = l; i <= r; i++) dp[i][0] = 0;

	for(int i = l; i <= m; i++){
		for(int j = m + 1; j <= r; j++){
			if(rat[i] < 1 && rat[j] < 1) continue;
			dp[i][0] += dp[i][1]*dp[j][1]*(rat[i]/(rat[i] + rat[j]));
			dp[j][0] += dp[i][1]*dp[j][1]*(rat[j]/(rat[i] + rat[j]));
		}
	}

	for(int i = l; i <= r; i++) dp[i][1] = dp[i][0];
}

int main(){

	fastio;

	cin >> n;
	in.resize(n - 1);
	int eu;
	cin >> eu;
	fr(i, n - 1) cin >> in[i];

	sort(all(in));

	int k = n;
	while(__builtin_popcount(k) != 1) k++;

	int zeros = k - n;

	int p = 0;

	for(int i = 1; i <= k; i++){
		if(i == 1){
			rat[i] = eu;
			continue;
		}
		if(i%2 == 0 && zeros > 0){
			rat[i] = 0;
			zeros--;
		}
		else{
			rat[i] = in[p];
			p++;
		}
	}

	//frr(i, k) dbg(rat[i]);

	solve(1, k);

	cout << setprecision(12) << dp[1][1] << endl;


}
