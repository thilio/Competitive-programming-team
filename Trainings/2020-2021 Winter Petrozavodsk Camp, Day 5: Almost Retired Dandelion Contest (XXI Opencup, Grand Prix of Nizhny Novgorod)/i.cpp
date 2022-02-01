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

const ll INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

ll dp[2002][2]; 

ll n, s;

vector<pll> v; // .fst = p; .snd = c; 

int main(){

	fastio;
	cin >> n >> s;

	v.resize(n);

	fr(i, n) cin >> v[i].snd;
	fr(i, n) cin >> v[i].fst;  

	sort(all(v));
	reverse(all(v));

	for(int i = 0; i <= 2000; i++){
		for(int j = 0; j < 2; j++){
			dp[i][j] = INF;
		}
	}

	dp[0][0] = 0;

	for(int i = 0; i < n; i++){
		
		for(ll j = 0; j <= min(i + 1, 2000); j++){
			if(j > 0){
				dp[j][1] = ((j - 1)*v[i].fst + v[i].snd) + dp[j - 1][0]; 
			}
			dp[j][1] = min(dp[j][1], dp[j][0]);
			dp[j][1] = min(dp[j][1], INF);
		}

		for(int j = 0; j <= 2000; j++){
			dp[j][0] = dp[j][1];
		}
	}

	int ans = 0;

	for(int j = 0; j <= 2000; j++){
		if(dp[j][0] <= s) ans = j;
	}

	cout << ans << endl;




}
