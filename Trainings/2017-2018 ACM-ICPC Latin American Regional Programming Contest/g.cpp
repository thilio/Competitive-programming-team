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
const ll MOD = 1e9+7;

int f[100100], l[100100], r[100100];
ll memo[100100][2][2];
int n;

void pd(int node){
	if(node == 0){
		memo[node][0][0] = memo[node][1][1] = 1;
		memo[node][0][1] = memo[node][1][0] = 0;
		return;
	}
	int lson = l[node];
	int rson = r[node];
	pd(lson);
	pd(rson);


	memo[node][0][0] = memo[lson][1][1]*memo[rson][1][1];
	memo[node][0][0] %= MOD;

	memo[node][0][1] = memo[lson][1][0]*memo[rson][1][0];
	memo[node][0][1] %= MOD;
	memo[node][0][1] += memo[lson][1][0]*memo[rson][1][1];
	memo[node][0][1] %= MOD;
	memo[node][0][1] += memo[lson][1][1]*memo[rson][1][0];
	memo[node][0][1] %= MOD;

	memo[node][1][0] = memo[lson][0][1]*memo[rson][0][1];
	memo[node][1][0] %= MOD;
	memo[node][1][0] += memo[lson][1][1]*memo[rson][0][1];
	memo[node][1][0] %= MOD;
	memo[node][1][0] += memo[lson][0][1]*memo[rson][1][1];
	memo[node][1][0] %= MOD;

	ll tot1 = memo[lson][0][0] + memo[lson][0][1] + memo[lson][1][0] + memo[lson][1][1];
	tot1%=MOD;
	ll tot2 = memo[rson][0][0] + memo[rson][0][1] + memo[rson][1][0] + memo[rson][1][1];
	tot2%=MOD;
	ll tot = tot1*tot2;
	tot %= MOD;

	memo[node][1][1] = (4*MOD + tot - memo[node][1][0] - memo[node][0][1] - memo[node][0][0])%MOD;

	if(f[node] == 0){
		memo[node][0][1] += memo[node][1][1];
		memo[node][0][1] %= MOD;
		memo[node][1][1] = 0;

		memo[node][0][0] += memo[node][1][0];
		memo[node][0][0] %= MOD;
		memo[node][1][0] = 0;
	}

	if(f[node] == 1){
		memo[node][1][1] += memo[node][0][1];
		memo[node][1][1] %= MOD;
		memo[node][0][1] = 0;

		memo[node][1][0] += memo[node][0][0];
		memo[node][1][0] %= MOD;
		memo[node][0][0] = 0;
	}
}

int main(){

	fastio;
	cin >> n;

	frr(i,n) cin >> l[i] >> r[i] >> f[i];

	pd(1);

	ll ans = memo[1][0][1] + memo[1][1][0];

	fr(i,2){
		fr(j,2){
			//dbg(memo[1][i][j]);
		}
	}
	ans %= MOD;
	cout << ans << endl;
}
