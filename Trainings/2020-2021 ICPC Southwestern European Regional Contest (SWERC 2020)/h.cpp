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
const int MAXN = 1e5 + 10;

#define oper(a, b) a + b
#define NEUT 0

namespace seg{
	vi seg(1, NEUT), lft(1, 0), rgt(1, 0);
	int rt(0);

	int new_node(int v, int l = 0, int r = 0){
		seg.pb(v);
		lft.pb(l);
		rgt.pb(r);
		return (int)(seg.size()) - 1;
	}

	int update(int nd, int l, int r, int pos, int val){
		int ks = new_node(seg[nd], lft[nd], rgt[nd]);
		if (l == r){
			seg[ks] = val;
			return ks;
		}

		int m = (l + r)/2, ps;
		if (pos <= m)
			ps = update(lft[nd], l, m, pos, val), lft[ks] = ps;
		else
			ps = update(rgt[nd], m + 1, r, pos, val), rgt[ks] = ps;
	
		seg[ks] = oper(seg[lft[ks]], seg[rgt[ks]]);
		return ks;
	}

	int query(int nd, int l, int r, int ql, int qr){
		if (r < ql or qr < l)
			return NEUT;
		if (ql <= l and r <= qr)
			return seg[nd];
		int m = (l + r)/2;
		return oper(query(lft[nd], l, m, ql, qr), query(rgt[nd], m + 1, r, ql, qr));
	}

	int update(int l, int r, int pos, int val){ return rt = update(rt, l, r, pos, val); }
}

int esta[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n;
	cin>>n;
	// dbg(n);

	string s;
	getline(cin, s);

	vi root = {0}; // dia 0

	fr(i, n){
		getline(cin, s);
		stringstream ss(s);

		vi qry;
		int x;
		while (ss>>x){
			qry.pb(x);
		}

		int rt = -1;
		for (auto y : qry){
			if (esta[abs(y)])
				rt = seg::update(0, n, abs(y), 0);
			else{
				rt = seg::update(0, n, abs(y), 1);
				esta[abs(y)] = 1;
			}
		}

		if (rt == -1)
			root.pb(root.back());
		else
			root.pb(rt); // raiz da ultima alteração
	}

	int ans = 0, d;

	fr(i, n){
		cin>>d;
		int y = seg::query(root[d], 0, n, ans, n); // maior ou igual a ans
		ans = (ans + y) % n;
	}

	cout<<ans<<endl;
}