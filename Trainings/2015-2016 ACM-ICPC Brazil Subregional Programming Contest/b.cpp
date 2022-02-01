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
int n,c;
int v[200200];
int memo[200200][2];

void solve(){

	for(int i = n - 1; i >= 0; i--){
		for(int tem = 0; tem < 2; tem++){
			memo[i][tem] = memo[i + 1][tem];
			if(tem == 0){
				memo[i][tem] = max(memo[i][tem], memo[i + 1][1] - (v[i] + c));
			}
			else{
				memo[i][tem] = max(memo[i][tem], v[i] + memo[i+1][0]);
			}
		}
	}


}

int main(){

	fastio;

	cin >> n >> c;
	//ms(memo,-1);
	fr(i,n) cin >> v[i];
	solve();
	cout << memo[0][0] << endl;
}
