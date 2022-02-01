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
const ll MOD = (1ll << 31) - 1;

int v[3000];
int n;
ll memo[2200][2200];

ll dp(int ind, int base){
	if(ind == n + 1) return 1;

	ll& pdm = memo[ind][base];
	if(pdm != -1) return pdm;

	pdm = 0;

	int fim = v[ind - 1];
	if(fim > base){
		if(v[ind] < base){
			pdm = dp(ind + 1, fim);
		}
		else if(v[ind] > fim){
			pdm = dp(ind + 1, base);
		}
		else if(v[ind] > base && v[ind] < fim){
			pdm = (dp(ind + 1, base) + dp(ind + 1, fim))%MOD;
		}
	}
	else if(base > fim){
		if(v[ind] > base){
			pdm = dp(ind + 1, fim);
		}
		else if(v[ind] < fim){
			pdm = dp(ind + 1, base);
		}
		else if(v[ind] < base && v[ind] > fim){
			pdm = (dp(ind + 1, base) + dp(ind + 1, fim))%MOD;
		}	
	}
	return pdm;
}

int main(){

	fastio;

	ms(memo, - 1);

	cin >> n;
	fr(i, n + 1) cin >> v[i];

	cout << dp(2, v[0]) << endl;



}
