#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define endl '\n'
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
const ll llINF = 1e18;
const int MOD = 1e9+7;

ll n, m, start, final;
bool esta[10100];
vector<array<ll, 3>> edges;

ll global[10100][2], bank[10100][2];

ll val_b[1010], val_g[1010];

void Bellman_Ford(){
	ms(global, -1); ms(bank, -1);

	global[start][0] = 0; bank[start][0] = 0;

	for(int i = 1; i <= n; i++){
		for(auto x: edges){
			ll u = x[0];
			ll v = x[1];
			ll cost = x[2];

			if(!esta[u] || !esta[v]){
				if(global[u][0] != -1 && (global[v][1] == -1 || global[v][1] > global[u][0] + cost)){
					global[v][1] = global[u][0] + cost; 
				}
			}

			if(esta[u] && esta[v]){
				if(bank[u][0] != -1 && (bank[v][1] == -1 || bank[v][1] > bank[u][0] + cost)){
					bank[v][1] = bank[u][0] + cost;
				}
			}
		}

		for(int j = 1; j <= n; j++){
			bank[j][0] = bank[j][1];
			global[j][0] = global[j][1];
		}

		val_b[i] = bank[final][1];
		val_g[i] = global[final][1];
	}
}

ll teto(ll a, ll b){
	return (a + b - 1)/b;
}

ll chao(ll a, ll b){
	return a/b;
}

ll compare(int i){
	if(val_b[i] == -1) return -1;

	ll r, l;

	r = llINF;
	l = -1;

	for(int j = 1; j <= n; j++){
		if(val_g[j] == -1) continue;
		if(j < i){
			if(val_g[j] <= val_b[i]) return -1;
			r = min(r, teto(val_g[j] - val_b[i], i - j) - 1);
		}
		if(j == i){
			if(val_g[j] <= val_b[i]) return -1;
		}
		if(j > i){
			if(val_g[j] >= val_b[i]) continue;
			l = max(l, chao(val_b[i] - val_g[j], j - i) + 1);
		}
	}

	if(l > r) return -1;
	return r;
}

int main(){

	fastio;

	cin >> n >> m >> start >> final;

	fr(i, m){
		ll x, y, c;
		cin >> x >> y >> c;
		edges.pb({x, y, c});
		edges.pb({y, x, c});
	}

	int P;
	cin >> P;
	fr(i, P){
		int x; cin >> x; esta[x] = true;
	}

	Bellman_Ford();

	ll best = -1;

	for(int i = 1; i <= n; i++){
		best = max(best, compare(i));
	}

	if(best == llINF){
		cout << "Infinity" << endl;
	}
	else if(best == -1){
		cout << "Impossible" << endl;
	}
	else{
		cout << best << endl;
	}
}
