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

ll v[200200];
ll memo[100][200200];
ll n,a,b;

ll dp(int i,int soma){
	if(soma > b) return 0;
	if(i == n){
		if(soma >= a) return 1;
		return 0;
	}

	ll& pdm = memo[i][soma];
	if(pdm != -1) return pdm;
	pdm = 0;

	pdm += dp(i + 1, soma + v[i]);
	pdm += dp(i + 1, soma);

	pdm %= MOD;
	return pdm;
}


int main(){

	fastio;

	cin >> n >> a >> b;
	fr(i,n) cin >> v[i];
	ms(memo,-1);

	cout << dp(0,0) << endl;
}
