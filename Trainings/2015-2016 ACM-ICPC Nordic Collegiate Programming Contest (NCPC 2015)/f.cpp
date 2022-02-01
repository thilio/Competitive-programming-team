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

int memo[10010][110];
int n,r;
int v[1010];

bool resp;

int dp(int at,int ind){
	if(ind == n) return 1;

	int &pdm = memo[at][ind];
	if(pdm != -1) return pdm;

	pdm = 0;
	if(at + v[ind] <= r) pdm |= dp(at + v[ind], ind + 1);
	if(at - v[ind] >= 0) pdm |= dp(at - v[ind], ind + 1);

	return pdm;
}

bool solve(){
	cin >> r >> n;

	fr(i,n){
		int a,b;
		cin >> a >> b;
		v[i] = b - a;
	}

	int ans = 0;
	ms(memo,-1);

	for(int i = 0; i <= r; i++){
		ans |= dp(i,0);
	}

	return ans;
}


int main(){

	fastio;

	int T;
	cin >> T;
	resp = true;
	while(T--){
		resp = resp & (solve());
	}

	if(resp) cout << "possible" << endl;
	if(!resp) cout << "impossible" << endl;

}
