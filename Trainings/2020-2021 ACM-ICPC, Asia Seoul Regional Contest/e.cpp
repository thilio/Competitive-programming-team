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
int n;
int d[1000100];
bool dp[1000100][2][2];

void pd(){
	if(d[n - 1] == 0){
		dp[n - 1][0][0] = dp[n-1][1][1] = true;
	}
	if(d[n -1] == 1){
		dp[n -1][1][0] = dp[n-1][0][1] = true;
	}

	for(int i = n - 2; i >= 0; i--){
		for(int p1 = 0; p1 < 2; p1++){
			for(int p2 = 0; p2 < 2; p2++){
				for(int f1 = 0; f1 < 2; f1++){
					for(int f2 = 0; f2 < 2; f2++){
						if(abs(p1 + f1 - p2 - f2) == d[i]){
							dp[i][p1][p2] |= dp[i + 1][f1][f2];
						}
					}
				}
			}
		}
	}
}

int main(){

	fastio;

	cin >> n;
	fr(i,n){
		cin >> d[i];
	}

	pd();

	for(int i = 4; i >= 0;  i--){
		for(int j = 0; j < 2; j++){
			for(int k = 0; k < 2; k++){
				//cout << dp[i][j][k] << endl;
			}
		}
	}

	if(dp[0][0][0]) cout << "YES" << endl;
	else cout << "NO" << endl;



}
