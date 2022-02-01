#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

// #define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(), x.end()

typedef long long int ll;

#define int ll

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;
const ll mod = 1e9 + 7;

typedef pair<pii, pii> piiii;

int lazy[4 *MAXN];
piiii seg[4 * MAXN];

string s; // swap o par e swap dentro

pii operator+(pii a, pii b){
	return make_pair( (a.fst + b.fst) % mod, (a.snd + b.snd) % mod );
}
pii operator*(pii a, int b){
	return make_pair( (a.fst * b) % mod, (a.snd * b) % mod);
}

piiii concat(piiii l, piiii r){
	piiii ans = {{0, 0}, {0, 0}};

	ans.fst = ((l.fst * r.fst.fst) + (l.snd * r.fst.snd));
	ans.snd = ((l.fst * r.snd.fst) + (l.snd * r.snd.snd));
	return ans;
}

void build(int node, int l, int r){
	if (l == r){
		if (s[l - 1] == 'A')
			seg[node] = {{1, 1}, {0, 1}};
		else
			seg[node] = {{1, 0}, {1, 1}};
	}
	else{
		int m = (l + r)/2;
		build(node<<1, l, m);
		build(node<<1|1, m + 1, r);

		seg[node] = concat(seg[node<<1], seg[node<<1|1]);
	}
}

void unlazy(int node, int l, int r){
	if (l != r){
		lazy[node<<1] += lazy[node];
		lazy[node<<1|1] += lazy[node];
	}

	if (lazy[node] % 2){
		swap(seg[node].fst, seg[node].snd);
		swap(seg[node].fst.fst, seg[node].fst.snd);
		swap(seg[node].snd.fst, seg[node].snd.snd);
	}

	lazy[node] = 0;
}

void update(int node, int l, int r, int ql, int qr){
	unlazy(node, l, r);
	if (r < ql or qr < l)
		return;
	if (ql <= l and r <= qr){
		lazy[node]++;
		unlazy(node, l, r);
		return;
	}

	int m = (l + r)/2;
	update(node<<1, l, m, ql, qr);
	update(node<<1|1, m + 1, r, ql, qr);

	seg[node] = concat(seg[node<<1], seg[node<<1|1]);
}

piiii query(int node, int l, int r, int ql, int qr){
	unlazy(node, l, r);
	if (r < ql or qr < l)
		return {{1, 0}, {0, 1}}; // neutro
	if (ql <= l and r <= qr){
		return seg[node];
	}

	int m = (l + r)/2;

	piiii a = query(node<<1, l, m, ql, qr);
	piiii b = query(node<<1|1, m + 1, r, ql, qr);

	return concat(a, b);
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, q;

	cin>>n>>q;
	cin>>s;

	build(1, 1, n);

	ll typ, l, r, a, b;
	while (q--){ // esta com define int ll
		cin>>typ;
		if (typ == 2){
			cin>>l>>r>>a>>b;

			piiii aux = query(1, 1, n, l, r);
			ll ansa = (a * aux.fst.fst + b * aux.fst.snd) % mod;
			ll ansb = (a * aux.snd.fst + b * aux.snd.snd) % mod;
			cout<<ansa<<' '<<ansb<<endl;
		}
		else{
			cin>>l>>r;
			update(1, 1, n, l, r);
		}
	}
}