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

vi adj[100100];
int pai[100100];
vi filhos[100100];
int n;

ll memo[100100][4];
ll pre[100100][4];
ll suf[100100][4];
ll t[100100];

void dfs(int v, int p){
	pai[v] = p;
	for(auto x: adj[v]) if(x != p) dfs(x, v);
}

void calc(int v){
	int k = filhos[v].size();
	t[k - 1] = 0;
	for(int i = k - 1; i > 0; i--){
		int x = filhos[v][i];
		t[i - 1] = (t[i]*memo[x][3])%MOD;
		ll termo = memo[x][2];
		if(i!= k - 1) termo = (termo*suf[i + 1][3]) %MOD;
		t[i - 1] = (t[i - 1] + termo)%MOD; 
	}
}

void dp(int v){
	
	if(memo[v][0] != -1) return;

	if(filhos[v].empty()){
		memo[v][1] = 0;
		memo[v][2] = 1;
		memo[v][3] = 1;
		return;
	}

	int k = filhos[v].size();
	for(auto x: filhos[v]){
		dp(x);
	}
	fr(i, k){
		int x = filhos[v][i];
		if(i == 0){
			pre[i][1] = memo[x][1];
			pre[i][2] = memo[x][2];
			pre[i][3] = memo[x][3];
		}
		else{
			pre[i][1] = (pre[i - 1][1]*memo[x][1])%MOD;
			pre[i][2] = (pre[i - 1][2]*memo[x][2])%MOD;
			pre[i][3] = (pre[i - 1][3]*memo[x][3])%MOD;	
		}
	}
	for(int i = k - 1; i >= 0; i--){
		int x = filhos[v][i];
		if(i == k - 1){
			suf[i][1] = memo[x][1];
			suf[i][2] = memo[x][2];
			suf[i][3] = memo[x][3];
		}
		else{
			suf[i][1] = (suf[i + 1][1]*memo[x][1])%MOD;
			suf[i][2] = (suf[i + 1][2]*memo[x][2])%MOD;
			suf[i][3] = (suf[i + 1][3]*memo[x][3])%MOD;	
		}
	}

	calc(v);
	frr(b, 3){
		ll &pdm = memo[v][b];
		pdm = 0;

		if(b == 1){
			fr(i,k){
				int x = filhos[v][i];
				ll termo = memo[x][2];
				if(i != 0) termo = (termo*pre[i - 1][3])%MOD;
				termo = (termo*t[i])%MOD;
				pdm = (pdm + termo)%MOD;
			}
		}
		if(b == 2){
			pdm = suf[0][1];
			fr(i, k){
				int x = filhos[v][i];
				ll termo = memo[x][2];
				if(i != 0) termo = (termo*pre[i - 1][3])%MOD;
				if(i != k - 1) termo = (termo*suf[i + 1][3])%MOD;
				pdm = (pdm + termo)%MOD;
			}
		}
		if(b == 3){
			pdm = suf[0][1];
			fr(i, k){
				int x = filhos[v][i];
				ll termo = memo[x][2];
				if(i != 0) termo = (termo*pre[i - 1][1])%MOD;
				if(i != k - 1) termo = (termo*suf[i + 1][1])%MOD;
				pdm = (pdm + termo)%MOD;
			}
			pdm = (pdm + memo[v][1])%MOD;
		}
	}
}


int main(){

	fastio;

	cin >> n;

	fr(i, n - 1){
		int u,v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	} 

	dfs(1, -1);
	frr(i,n) filhos[pai[i]].pb(i);
	ms(memo, -1);
	dp(1);

	cout << memo[1][3] << endl;


}
