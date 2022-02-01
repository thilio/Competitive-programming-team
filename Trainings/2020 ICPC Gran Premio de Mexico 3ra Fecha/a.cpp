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

int T, P;

int e[200], d[200], s[200];

int dp[2000][110][110];

int main(){
	cin >> T >> P;
	fr(i, T) cin >> e[i];
	frr(i, P) cin >> d[i];
	frr(i, P) cin >> s[i];

	ms(dp, 0);

	for(int mask = (1 << T) - 1; mask > 0; mask--){
		for(int p = P; p > 0; p--){
			for(int f = 0; f <= 100; f++){
				// skip
				dp[mask][p][f] = dp[mask][p + 1][f];

				//solve
				if(f >= d[p]){
					dp[mask][p][f] = max(dp[mask][p][f], s[p] + dp[mask][p + 1][f - d[p]]); 
				}

				//change
				fr(i, T){
					if((mask&(1 << i)) == 0){
						dp[mask][p][f] = max(dp[mask][p][f], dp[mask^(1 << i)][p][e[i]]);
					}
				}
			}
		}
	}

	int mx = 0;

	fr(i, T) mx = max(mx, dp[1 << i][1][e[i]]);

	cout << mx << endl;


	

	fastio;

}
