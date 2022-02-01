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

ll fat[70];
int n;

ll memo[61][61][61][61][2];

ll dp(int p1, int p2, int p3, int p4, bool ok){
	if(p1 + p2 + p3 + p4 == 0) return ok;

	ll& pdm = memo[p1][p2][p3][p4][ok];
	if(pdm != - 1) return pdm;
	pdm = 0;
	frr(i,p1){
		pdm += dp(i - 1, p2 + (p1 - i), p3,p4,ok);
	}
	frr(i,p2){
		pdm += dp(p1, i - 1, p3 + (p2 - i),p4,ok);
	}
	frr(i,p3){
		pdm += dp(p1, p2, i - 1,p4 + (p3 - i),true);
	}

	if(p4){
		pdm += dp(p1,p2,p3,p4 - 1, true);
	}

	pdm %= MOD;

	return pdm;
}

int main(){

	fastio;
	cin >> n;
	fat[0] = 1;

	for(ll i = 1; i <= n; i++){
		fat[i] = fat[i - 1]*i;
		fat[i] %= MOD;
	}

	ms(memo,-1);

	cout << (fat[n] - dp(n,0,0,0,0) + MOD)%MOD << endl;


}
