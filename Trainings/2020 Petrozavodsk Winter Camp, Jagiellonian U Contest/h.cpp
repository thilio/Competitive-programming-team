#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 3e2 + 10;

int n, m, vx[MAXN], vy[MAXN];
vector<pair<int, double>> adj[MAXN];

double dist(int i, int j){
	ll x = vx[i] - vx[j];
	ll y = vy[i] - vy[j];
	
	x = x * x;
	y = y * y;

	return sqrt(x + y);
}

bool vis[MAXN][MAXN][2];
double memo[MAXN][MAXN][2];

double pd(int l, int r, int at){ // 0 para l e 1 para r
	if (vis[l][r][at] != 0)
		return memo[l][r][at];

	vis[l][r][at] = 1;
	
	double &pdm = memo[l][r][at];
	pdm = 0;


	if (l < r){
		if (at == 0)
			for (auto x : adj[l])
				if (l < x.fst and x.fst < r){
					pdm = max(pdm, pd(x.fst, r, 0) + x.snd);
					pdm = max(pdm, pd(l, x.fst, 1) + x.snd);
				}

		if (at == 1)		
			for (auto x : adj[r])
				if (l < x.fst and x.fst < r){
					pdm = max(pdm, pd(x.fst, r, 0) + x.snd);
					pdm = max(pdm, pd(l, x.fst, 1) + x.snd);
				}
	}		
	else{
		if (at == 0)
			for (auto x : adj[l])
				if ((l < x.fst) or (x.fst < r)){
					pdm = max(pdm, pd(x.fst, r, 0) + x.snd);
					pdm = max(pdm, pd(l, x.fst, 1) + x.snd);
				}

		if (at == 1)		
			for (auto x : adj[r])
				if ((x.fst < r) or (l < x.fst)){
					pdm = max(pdm, pd(x.fst, r, 0) + x.snd);
					pdm = max(pdm, pd(l, x.fst, 1) + x.snd);
				}	
	}
	
	return pdm;
}

void solve(){
	cin>>n;

	frr(i, n){
		cin>>vx[i]>>vy[i];
		adj[i].clear();
	}
	
	cin>>m;

	int x, y;
	fr(i, m){
		cin>>x>>y;
		double d = dist(x, y);

		adj[x].pb({y, d});
		adj[y].pb({x, d});
	}

	frr(i, n)
		frr(j, n)
			fr(k, 2)
				vis[i][j][k] = 0;

	double ans = 0;

	for (int i = 1; i < n; i++)
	    for (auto [j, d] : adj[i])
	    	if (i < j){
				ans = max(ans, pd(i, j, 0) + d); // saio do l
				ans = max(ans, pd(i, j, 1) + d); // saio do r
				ans = max(ans, pd(j, i, 0) + d); // saio do l
				ans = max(ans, pd(j, i, 1) + d); // saio do r
	    	}

	cout<<setprecision(12)<<fixed;
	cout<<ans<<endl;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin>>T;
	while (T--)
		solve();
}