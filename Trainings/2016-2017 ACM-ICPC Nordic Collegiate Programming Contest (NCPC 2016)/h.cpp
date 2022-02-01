#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(ll i=0;i<n;i++)
#define frr(i,n)	for(ll i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long ll;
typedef pair<ll,ll> pii;
typedef vector<ll> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const ll INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
ll n;
vector<ll> comp[750750];
map<ll, ll> dimtoi;
map<ll, ll> itodim;

ll tudo;

vi adj[750750];
ll vis[750750];
bool ja[750750];

void dfs(ll x, ll c){
	vis[x] = 1;
	if(x <= n) comp[c].pb(x);
	for(auto y: adj[x]) if(!vis[y]) dfs(y, c);
}

ll solve(ll j){
	ll sum = 0;
	ll best = 0, ap = 0;
	fr(i, comp[j].size()){
		ll u = comp[j][i];
		if(i == 0){
		    best = MOD;
		    if(adj[u].size() == 1) ap = 1;
			for(auto x: adj[u]){
				sum += itodim[x];
				ja[x] = true;
				best = min((ll)itodim[x], best);
 			}
		}
		else{
			ll nova = 0;
			ll q_nova;
			for(auto x: adj[u]){
				if(!ja[x]){
					nova++;
					sum += itodim[x];
					q_nova = x;
				}
				ja[x] = true;
			}
			if(nova >= 2) assert(0);
			if(nova == 0){
				best = sum;
				ap = 1;
			}
			if(nova == 1){
				if(ap) best = itodim[q_nova] + best;
				else best = min(itodim[q_nova] + best, sum - itodim[q_nova]);
			}
		}
	}

	return best;
}

int main(){

	fastio;

	cin >> n;

	ll ct = n;
	frr(i, n){
		ll x, y;
		cin >> x >> y;
		tudo += x;
		tudo += y;

		if(!dimtoi.count(x)){
			dimtoi[x] = ++ct;
			itodim[ct] = x;
		}
		if(!dimtoi.count(y)){
			dimtoi[y] = ++ct;
			itodim[ct] = y;
		}

		adj[i].pb(dimtoi[x]);
		
		adj[dimtoi[x]].pb(i);
		
		if(x != y){
			adj[i].pb(dimtoi[y]);
			adj[dimtoi[y]].pb(i);	
		}
	}

	ll c = 0;
	frr(i, n){
		if(vis[i] == 0){
			c++;
			dfs(i, c);
		}
	}

	//for(auto x: comp[1]) dbg(x);

	ll ans = 0;
	frr(i, c){
		ans += solve(i);
	}

	//dbg(ans);
	//dbg(tudo);

	cout << tudo - ans << endl;



}
