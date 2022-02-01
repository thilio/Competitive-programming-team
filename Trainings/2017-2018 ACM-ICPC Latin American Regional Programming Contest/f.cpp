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
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

#define int long long int

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int n;

ll seg[4 * MAXN];

void modfy(ll node, ll l, ll r, ll pos, ll val){
	if (r < pos or pos < l) // out of bounds
		return;
	if (l == r){
		seg[node] = max(seg[node], val);
		return;
	}

	ll meio = (l + r)/2;
	modfy(node * 2, l, meio, pos, val);
	modfy((node * 2) + 1, meio + 1, r, pos, val);
	seg[node] = max(seg[node * 2], seg[(node * 2) + 1]);
}

ll query(ll node, ll l, ll r, ll ql, ll qr){
	if (r < ql or qr < l) // out of bounds
		return 0;
	if (ql <= l and r <= qr){
		return seg[node];
	}

	ll meio = (l + r)/2;
	return max(
		query(node * 2, l, meio, ql, qr),
		query((node * 2) + 1, meio + 1, r, ql, qr));
}


vector< tuple<int, int, ll> > v;
map<int, int> crdb, crdf;

ll ans[MAXN];

map<pair<int, int>, int> existe;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n;

	int b, f, cnt;
	ll d;
	vector<ll> bb, ff;

	cnt = 0;
	fr(i, n){
		cin>>b>>f>>d;
		if (existe.count({b, f})){ // já existe
			get<2>(v[existe[{b, f}]]) += (ll)d;
			continue;
		}

		existe[{b, f}] = cnt++;

		v.pb({b, f, d});
		bb.pb(b);
		ff.pb(f);
	}

	// for (auto e : v){
	// 	tie(b, f, d) = e;
	// 	cout<<b<<' '<<f<<' '<<d<<endl;
	// }

	n = v.size();

	sort(all(bb));
	sort(all(ff));

	cnt = 1;
	for (int e : bb)
		if (!crdb.count(e))
			crdb[e] = cnt++;
		
	cnt = 1;
	for (int e : ff)
		if (!crdf.count(e))
			crdf[e] = cnt++;


	fr(i, v.size()){
		tie(b, f, d) = v[i];
		v[i] = {crdb[b], crdf[f], d};
	} // ok, comprimi as coordenadas

	sort(all(v));

	// for (auto e : v){
	// 	tie(b, f, d) = e;
	// 	dbg(b);
	// 	dbg(f);
	// 	dbg(d);
	// 	chapa;
	// }

	int p = 0, pp;
	ll mans = 0;

	while (p < n){
		pp = p;
		
		while (pp < n and get<0>(v[pp]) == get<0>(v[p])){
			ans[pp] = query(1, 0, n, 0, get<1>(v[pp]) - 1) + get<2>(v[pp]);
			mans = max(mans, ans[pp]);
			pp++;
		}
		
		while (p < pp){
			modfy(1, 0, n, get<1>(v[p]), ans[p]);
			p++;
		}
		
		p = pp;
	}

	// fr(i, n)
	// 	dbg(ans[i]);

	cout<<mans<<endl;


}