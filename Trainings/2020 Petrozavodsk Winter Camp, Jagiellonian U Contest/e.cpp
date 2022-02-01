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

const int INF = 2e9 + 1000;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 2e6 + 10;

int n, q;

int seg[4*MAXN], ans[MAXN];

void update(int node, int l, int r, int pos, int val){
	if (pos < l or r < pos)
		return;	
	if (l == r){
		seg[node] =	val;
		return;
	}

	int m = (l + r)/2;
	update(node<<1, l, m, pos, val);
	update(node<<1|1, m + 1, r, pos, val);

	seg[node] = max(seg[node<<1], seg[node<<1|1]);
}

int query(int node, int l, int r, int ql, int qr){
	if (qr < l or r < ql)
		return -INF;
	if (ql <= l and r <= qr)
		return seg[node];
	int m = (l + r)/2;

	return max(query(node<<1, l, m, ql, qr), query(node<<1|1, m + 1, r, ql, qr));
}

map<int, int> crd;

typedef tuple<int, int, int, int> tup;

vii lim;
vector<tup> event;
// 0 in bar, 1 query, 2 out bar


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n>>q;

	int cx, cy, r;
	fr(i, n){
		cin>>cx>>cy>>r;
		crd[cx];

		event.pb({cy - r, 0, cx, cy + r});
		event.pb({cy + r, 2, cx, cy - r});
	}

	int px, py, qx, qy, ymn, ymx;
	fr(i, q){
		cin>>px>>py>>qx>>qy>>ymn>>ymx;
		crd[px];
		crd[qx];
		lim.pb({min(px, qx), max(qx,px)});
		event.pb({ymn, 1, i, ymx});
	}

	int cnt = 1;
	for (auto &e : crd)
		e.snd = cnt++;

	fr(i, 2*n)
		get<2>(event[i]) = crd[get<2>(event[i])];

	fr(i, q)	
		lim[i] = {crd[lim[i].fst], crd[lim[i].snd]};

	sort(all(event));

	fr(i, 4*MAXN) seg[i] = -INF;


	int a, b, c, d;
	for (auto x : event){
		tie(a, b, c, d) = x;

		if (b == 0)
			update(1, 1, cnt, c, d);
		else if (b == 2)
			update(1, 1, cnt, c, -INF);
		else{
			if (query(1, 1, cnt, lim[c].fst, lim[c].snd) < d)
				ans[c] = 1;
		}
	}

	fr(i, q)
		cout<<(ans[i]?"YES":"NO")<<endl;	
}