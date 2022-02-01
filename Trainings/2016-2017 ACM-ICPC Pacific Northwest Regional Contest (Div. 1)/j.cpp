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
const int MAXN = 2e5 + 10;

ll n, q, v[MAXN], seg[4 * MAXN];

ll build(int node, int l, int r){
	if (l == r){
		seg[node] = v[l];
		return seg[node];
	}
	int meio = (l + r)/2;
	return seg[node] = min( build(node<<1, l, meio), build(node<<1|1, meio + 1, r));
}

ll query(int node, int l, int r, int ql, int qr, ll val){
	if (r < ql or qr < l)
		return INF;
	
	if (l == r and seg[node] <= val){
		return l;
	}

	int meio = (l + r)/2;

	ll p = INF;
	if (seg[node<<1] <= val)
		p = query(node<<1, l, meio, ql, qr, val);

	if (p == INF and seg[node<<1|1] <= val)
		p = query(node<<1|1, meio + 1, r, ql, qr, val);

	return p;
}

int32_t main(){
	fastio;
	cin>>n>>q;
	frr(i, n)
		cin>>v[i];

	build(1, 1, n);	

	ll l, r, c, p;	
	while (q--){
		cin>>c>>l>>r;
		p = query(1, 1, n, l, r, c);
		while (p <= r){
			c %= v[p];
			p = query(1, 1, n, l, r, c);
		}
		cout<<c<<endl;
	}

}