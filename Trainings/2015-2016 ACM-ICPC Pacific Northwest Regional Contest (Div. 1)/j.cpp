#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
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

ll dp[10000003];

int main(){

	fastio;

	cout << setprecision(6) << fixed;

	ll e, es, ef;
	cin >> e >> es >> ef;
	dp[0] = 0;

	frr(i,e){
		dp[i] = 1;
		if(i - es > 0) dp[i] += dp[i - es];
		if(i - ef > 0) dp[i] += dp[i - ef];

		if(dp[i] > INF){
			cout << 0. << endl;
			return 0;
		}
	}

	double x = 225;
	double y = 200;
	cout << min(x/(dp[e] + 1), y/dp[e]) << endl;;
}
