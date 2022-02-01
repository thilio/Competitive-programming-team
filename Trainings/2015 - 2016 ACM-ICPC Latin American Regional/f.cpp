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
typedef tuple<int, bool, int, int> tp; 

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;


int p, v;
vector<pii> plants;
vector<pii> vtx;
vector<int> tudo;
map<int, int> compre;

int upper;

vector<tp> sweep;
// 0 é um segmento de cerca
// 1 é uma planta

bool seg[2000200];
bool lazy[2000200];

void unlazy(int node, int l, int r){
	if(lazy[node] == false) return;
	if((r - l + 1)%2) seg[node]^= 1;
	lazy[node] = 0;
	if(l != r){
		lazy[2*node]^=1;
		lazy[2*node + 1]^=1;
	}
}

bool query(int node, int l, int r, int p){
	unlazy(node, l, r);
	if(p < l || p > r) return 0;
	if(l == r) return seg[node];

	int m = (l + r)/2;

	return query(2*node,l ,m ,p)^query(2*node + 1,m + 1, r, p);
}

void update(int node, int l, int r, int a, int b){
	unlazy(node, l, r);
	if(r < a || l > b) return;
	if(a <= l && r <= b){
		lazy[node]^=1;
		unlazy(node, l, r);
		return;
	}
	int m = (l + r)/2;
	update(2*node,l , m, a, b);
	update(2*node + 1,m + 1, r, a, b);
	seg[node] = seg[2*node]^seg[2*node + 1];
}

void read(){
	cin >> p >> v;
	fr(i, p){
		int x, y;
		cin >> x >> y;
		plants.pb({x, y});
		tudo.pb(x);
		tudo.pb(y);
	}
	fr(i, v){
		int x, y;
		cin >> x >> y;
		vtx.pb({x, y});
		tudo.pb(x);
		tudo.pb(y);
	}
	sort(all(tudo));
	int ct = 0;
	for(auto x: tudo){
		if(!compre.count(x)) compre[x] = ++ct;
	}
	upper = ct;

	for(auto &x: plants){
		x.fst = compre[x.fst];
		x.snd = compre[x.snd];
	}
	for(auto &x: vtx){
		x.fst = compre[x.fst];
		x.snd = compre[x.snd];
	}
}

void build(){
	fr(i, plants.size()){
		pii x = plants[i];
		sweep.pb({x.fst, 1, x.snd, i + 1});
	}

	fr(i, vtx.size()){
		int nxt = (i + 1)%vtx.size();
		if(vtx[i].fst == vtx[nxt].fst){
			int mn = min(vtx[i].snd, vtx[nxt].snd);
			int mx = max(vtx[i].snd, vtx[nxt].snd);
			sweep.pb({vtx[i].fst, 0, mn, mx - 1});
		}
	}

	sort(all(sweep));
}

int main(){

	fastio;
	read();
	build();

	ll ans = 0;

	for(auto e: sweep){
		bool tipo; int x, a, b;
		tie(x, tipo, a, b) = e;
		if(tipo == true){
			if(!query(1, 1, upper, a)) ans += b;
	//		dbg(query(1, 1, upper, a));
	//		dbg(b);
		}
		else{
			update(1, 1, upper, a, b);
		}
	}

	cout << ans << endl;



}
