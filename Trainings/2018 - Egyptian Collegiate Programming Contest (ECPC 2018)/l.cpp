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
#define endl '\n'

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

pii seg[400400];
bool lazy[400400];

pii operator+(pii a, pii b){
	return {a.fst + b.fst, a.snd + b.snd};
}

void unlazy(int node, int l, int r){
	if(!lazy[node]) return;

	swap(seg[node].fst, seg[node].snd);
	if(l != r){
		lazy[2*node] ^= 1;
		lazy[2*node + 1] ^= 1;
	}
	lazy[node] = false;
}

void build(int node, int l, int r){
	lazy[node] = false;
	if(l == r){
		seg[node] = {1, 0};
		return;
	}
	int m = (l + r)/2;
	build(2*node,l,m);
	build(2*node + 1, m + 1, r);
	seg[node] = seg[2*node] + seg[2*node + 1];
}

pii query(int node, int l, int r, int a, int b){
	unlazy(node, l, r);
	if(b < l || a > r) return {0, 0};
	if(a <= l && r <= b) return seg[node];

	int m = (l + r)/2;
	return query(2*node, l, m, a, b) + query(2*node + 1, m + 1, r, a, b);
}

void update(int node, int l, int r, int a, int b){
	unlazy(node, l, r);
	if(b < l || a > r) return;
	if(a <= l && r <= b){
		lazy[node] = true;
		unlazy(node, l, r);
		return;
	}
	int m = (l + r)/2;
	update(2*node, l, m, a, b);
	update(2*node + 1, m + 1, r, a, b);
	seg[node] = seg[2*node] + seg[2*node + 1];

}

int main(){

	freopen("reflection.in", "r", stdin);

	fastio;
	int T;
	cin >> T;
	while(T--){
		build(1, 1, 100000);
		int q;
		cin >> q;
		while(q--){
			int x;
			cin >> x;
			pii a = query(1, 1, 100000, 1, x);
			cout << a.fst - a.snd << endl;
			if(x != 100000) update(1, 1, 100000, x + 1, 100000);
		}
	}
}
