#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

	#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 4e5 + 10;

// Segtree encontra todos os segmentos que contém um ponto
// # de segmentos que contém um ponto <= 32

int n;
vector< tuple<ll, ll, ll>> in;
set<int> seg[4 * MAXN];
map<ll, ll> crd; // compressão de coordenada

void insert(int node, int l, int r, int ul, int ur, int val){
	if (ur < l or r < ul)
		return;
	if (ul <= l and r <= ur){ // garda no primeiro segmento continudo no circulo
		seg[node].insert(val);
		return;
	}

	int meio = (l + r)/2;
	insert(node<<1, l, meio, ul, ur, val);
	insert(node<<1|1, meio + 1, r, ul, ur, val);
}

void remove(int node, int l, int r, int ul, int ur, int val){
	if (ur < l or r < ul)
		return;
	if (ul <= l and r <= ur){
		seg[node].erase(val);
		return;
	}

	int meio = (l + r)/2;
	remove(node<<1, l, meio, ul, ur, val);
	remove(node<<1|1, meio + 1, r, ul, ur, val);
}

set<int> qry;
void query(int node, int l, int r, int val){
	if (r < val or val < l)
		return;
	if (l <= val and val <= r){ // desce a árvore coletando os segmentos
		for (auto x : seg[node])
			qry.insert(x);
		if (l == r)
			return;
	}
	
	int meio = (l + r)/2;
	query(node<<1, l, meio, val);
	query(node<<1|1, meio + 1, r, val);
}

int32_t main(){
	fastio;
	cin>>n;

	ll c, x, y;
	set<ll> cmp;
	frr(i, n){
		cin>>c>>x>>y;
		in.pb({c, x, y});
		if (c == 1){
			cmp.insert(x - y);
			cmp.insert(x + y);
		}
		else
			cmp.insert(x);
	}

	int p = 0;
	for (ll u : cmp)
		crd[u] = ++p;

	frr(i, n){
		tie(c, x, y) = in[i - 1];

		if (c == 1)
			insert(1, 1, p, crd[x - y], crd[x + y], i);
		else{
			qry.clear();
			query(1, 1, p, crd[x]);

			ll ans = -1, xx, yy;
			for (auto u : qry){
				tie(ignore, xx, yy) = in[u - 1];
				if ((x - xx) * (x - xx) + (y - yy) * (y - yy) < yy * yy){
					remove(1, 1, p, crd[xx - yy], crd[xx + yy], u);
					ans = u;
					break;
				}
			}	
			cout<<ans<<endl;	
		}
	}
}