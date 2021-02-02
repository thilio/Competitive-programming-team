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

int n,q;

vi adja[100100];
vi adjb[100100];
ll f[100100];
ll g[100100];
ll dist[100100];
ll distd[100100][2];

ll diama;
ll diamb;

vector<ll> v;
ll pref[100100];

ll diam;

void reset(){
	v.clear();
	frr(i,n){
		adja[i].clear();
		dist[i] = 0;
		distd[i][0] = distd[i][1] = 0;
		f[i] = 0;
	}
	frr(i,q){
		adjb[i].clear();
		dist[i] = 0;
		distd[i][0] = distd[i][1] = 0;
		g[i] = 0;
		pref[i] = 0;
	}

	diama = 0;
	diamb = 0;
	diam = 0;
}

void dfs_longe_a(int v,int p){
	if(v == 1)
		dist[v] = 0;
	if(v != 1)
		dist[v] = dist[p] + 1;
	for(auto x : adja[v]){
		if(x == p) continue;
		dfs_longe_a(x,v);
	}
}
void dfs_longe_b(int v,int p){
	if(v == 1)
		dist[v] = 0;
	if(v != 1)
		dist[v] = dist[p] + 1;
	for(auto x : adjb[v]){
		if(x == p) continue;
		dfs_longe_b(x,v);
	}
}

void dfsa(int v,int p,int type){
	if(p == -1) distd[v][type] = 0;
	else distd[v][type] = distd[p][type] + 1;

	for(auto x : adja[v]){
		if(x == p) continue;
		dfsa(x,v,type);
	}
}

void dfsb(int v,int p,int type){
	if(p == -1) distd[v][type] = 0;
	else distd[v][type] = distd[p][type] + 1;

	for(auto x : adjb[v]){
		if(x == p) continue;
		dfsb(x,v,type);
	}
}

int main(){

	fastio;
	cout << setprecision(3) << fixed;
	while(cin >> n >> q){
		reset();

		fr(i,n - 1){
			int u,v;
			cin >> u >> v;
			adja[u].pb(v);
			adja[v].pb(u);
		}

		fr(i,q - 1){
			int u,v;
			cin >> u >> v;
			adjb[u].pb(v);
			adjb[v].pb(u);
		}

		dfs_longe_a(1, - 1);
		ll mx = 0;
		int longe = 1;
		frr(i,n){
			if(dist[i] >= mx){
				mx = dist[i];
				longe = i;
			}
		}

		dfsa(longe,-1, 0);
		frr(i,n){
			if(distd[i][0] >= diama){
				longe = i;
				diama = distd[i][0];
			}
		}
		
		dfsa(longe,-1,1);

		frr(i,n) f[i] = max(distd[i][0],distd[i][1]);

		dfs_longe_b(1, -1);
		mx = 0;
		longe = 1;
		frr(i,q){
			if(dist[i] >= mx){
				mx = dist[i];
				longe = i;
			}
		}
		dfsb(longe,-1,0);
		frr(i,q){
			if(distd[i][0] >= diamb){
				longe = i;
				diamb = distd[i][0];
			}
		}
		dfsb(longe,-1,1);
		frr(i,q) g[i] = max(distd[i][0],distd[i][1]);
		diam = max(diama,diamb);

		frr(i,q) v.pb(g[i]);
		sort(all(v));

		pref[q - 1] = v[q - 1];
		for(int i = q - 2; i >= 0; i--){
			pref[i] = pref[i + 1] + v[i];
		}

		ll ans = 0;

		frr(i,n){
			auto it = lower_bound(all(v), diam - f[i] - 1);
			int pos = (int)(it - v.begin());
			ans += pos*diam;
			ans += (q - pos)*f[i] + (q - pos) + pref[pos];
		}

		long double resp = ans;
		long double nn = n;
		long double qq = q;

		cout << resp/(nn*qq) << endl;
	}

}
