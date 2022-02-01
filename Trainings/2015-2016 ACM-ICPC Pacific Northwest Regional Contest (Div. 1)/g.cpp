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

ll n,r,w,h;
vector<pll> p;
map<ll,ll> m;
vector<ll> aux;

ll seg[400400];

bool comp(pll a, pll b){
	if(-a.fst*r + a.snd < -b.fst*r + b.snd) return true;
	if(-a.fst*r + a.snd > -b.fst*r + b.snd) return false;
	if(a.snd < b.snd) return true;
	return false;
}

void update(int node,int l,int r,int j, ll val){
	if(j < l || j > r) return;
	if(l == r && j == l){
		seg[node] = max(seg[node],val);
		return;
	}

	int m = (l + r)/2;
	update(2*node,l,m,j,val);
	update(2*node + 1,m + 1,r,j,val);

	seg[node] = max(seg[2*node],seg[2*node + 1]);
}

ll query(int node,int l,int r,int a,int b){
	if(b < l || a > r) return 0;
	if(a <= l && r <= b) return seg[node];

	int m = (l + r)/2;
	int q1 = query(2*node, l, m, a, b);
	int q2 = query(2*node+1, m + 1,r,a,b);

	return max(q1,q2);
}

int main(){

	fastio;

	cin >> n >> r >> w >> h;

	fr(i,n){
		ll x,y;
		cin >> x >> y;
		p.pb(mp(x,y));
		aux.pb(r*x + y);
	}

	sort(all(aux));
	int ct = 1;

	for(auto s: aux){
		if(m[s] != 0) continue;
		m[s] = ct++;
	}

	sort(all(p),comp);

    for(auto x : p){
		//cout << x.fst << ' '  << x.snd << endl;
	}

	int ans = 0;

	for(int i = p.size() - 1; i>= 0; i--){
		int tent = 1;
		pll at = p[i];
		int pp = m[at.snd + r*at.fst];
		tent += query(1,1,n,pp , n);
		//dbg(tent);
		ans = max(ans,tent);
		update(1,1,n,pp, tent);
		//dbg(seg[1]);
	}

	cout << ans << endl;
}
