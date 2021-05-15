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

ll n, k, g[4];
string s;

ll dp[100100][60];
ll ocu;

void pd(){
	frr(j, 50) dp[0][j] = -INF;
	for(int i = 1; i < n; i++){
		for(int j = 0; j <= 50; j++){
			dp[i][j] =  dp[i - 1][j];
			if(s[i] == '.'){
				if(j > 0 && i >= 2 && s[i - 1] == '#' && s[i - 2] == '.'){
					ll aux;
					if(i > 2) aux = dp[i - 3][j - 1];
					else{
						if(j == 1) aux = 0;
						else aux = - INF;
					}
					dp[i][j] = max(dp[i][j], aux);
				}
				if(s[i - 1] == '.'){
					ll aux;
					if(i > 1) aux = dp[i - 2][j];
					else{
						if(j) aux = -INF;
						else aux = 0;
					}
					dp[i][j] = max(dp[i][j], 1 + aux);
				}
			}
		}
	}
}

int main(){

	fastio;
	cin >> n >> k;
	frr(i, 3) cin >> g[i];

	cin >> s;

	for(auto x: s) if(x == '#') ocu++;

	pd();
	ll ans = 0;


	fr(i, 51){
		if(dp[n - 1][i] < 0) continue;
		ll resp = 0;
		resp = i*g[3] + dp[n - 1][i]*g[2];
		ll free = n - ocu - 2*i - 2*dp[n - 1][i];
		//dbg(free);
		if(free >= k){
			resp += k*g[1];
			ans = max(ans,resp);
		}
		else{
			resp += free*g[1];
			k -= free;
			if(g[1] > g[2]){
				//olar;
				//dbg(resp);
				if((k + 1)/2 <= dp[n - 1][i]){
					resp -= ((k + 1)/2)*g[2];
					resp += k*g[1];
				}
				else{
					resp -= dp[n - 1][i]*g[2];
					resp += 2*dp[n - 1][i]*g[1];
				}
			}
			else if(2*g[1] > g[2]){
				if(k/2 <= dp[n - 1][i]){
					resp -= (k/2)*g[2];
					resp += (k/2)*2*g[1];
				}
				else{
					resp -= dp[n - 1][i]*g[2];
					resp += 2*dp[n - 1][i]*g[1];
				}
			}
			k += free;

			ans = max(ans,resp);
		}
		//dbg(ans);
	}

	cout << ans << endl;
}
