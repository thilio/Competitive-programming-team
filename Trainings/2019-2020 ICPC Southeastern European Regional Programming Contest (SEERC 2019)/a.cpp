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

int n;
int m;
vi where[200200];

int p[800800];
int lazy[800800];
int len[200200];
int a[200200];

int sumz;
int cnt;

void unlazy(int node, int l, int r){
	if(lazy[node] == -1) return;
	p[node] = lazy[node];
	if(l != r){
		lazy[2*node] = lazy[node];
		lazy[2*node + 1] = lazy[node];
	}
	lazy[node] = -1; 
}

void build(int node, int l, int r){
	lazy[node] = -1;
	if(l == r){
		p[node] = l;
		len[l] = 1;
		a[l] = 1;
		return;
	}
	int m = (l + r)/2;
	build(2*node,l, m);
	build(2*node + 1, m + 1,r);
	p[node] = max(p[2*node], p[2*node + 1]);
}

int query(int node, int l,int r,int pos){
	unlazy(node, l , r);
	if(pos < l || pos > r) return -1;
	if(l == r) return p[node];
	int m = (l + r)/2;
	return max(query(2*node,l,m,pos), query(2*node + 1, m + 1, r,pos));
}

int query(int pos){		
	return query(1,1,n,pos);
}

void update(int node, int l, int r, int a, int b, int val){
	unlazy(node, l ,r);
	if(b < l || a > r) return;
	if(a <= l && r <= b){
		lazy[node] = val;
		unlazy(node, l , r);
		return;
	}
	int m = (l + r)/2;
	update(2*node,l,m,a,b,val);
	update(2*node + 1, m + 1, r, a, b, val);
	p[node] = max(p[2*node],  p[2*node + 1]);
}

void print(){
	ll ans = cnt + sumz;
	if(a[1] != a[n] && a[1] != 0 && a[n] != 0){
		int pn = query(n);
		ans -= len[1]/2;
		ans -= len[pn]/2;
		ans += (len[1] + len[pn])/2;
	}
	cout << ans << ' ';
}

void upd(int pos, int val){
	if(val == 0){
		cnt--;
		int aux = query(pos);
		if(aux + len[aux] - 1 == pos){
			sumz -= len[aux]/2;
			sumz += (len[aux] - 1)/2;
			len[aux]--;
		}
		else{
			sumz -= len[aux]/2;
			sumz += (pos - aux)/2;
			sumz += (aux + len[aux] - 1 - pos)/2;
			update(1,1,n,pos + 1, aux + len[aux] - 1, pos + 1);
			len[pos + 1] = aux + len[aux] - 1 - pos;
			len[aux] = pos - aux;
		}
		update(1,1,n, pos, pos, pos);
		len[pos] = 0;
		a[pos] = 0;
	}
	else{
		cnt++;
		a[pos] = -1;
		len[pos] = 1;
		update(1,1,n,pos,pos,pos);

		if(pos < n && a[pos + 1] == 1){
			sumz += (len[pos + 1] + 1)/2 - (len[pos + 1])/2;
			update(1,1,n,pos + 1, pos + len[pos + 1], pos);
			len[pos] = len[pos + 1] + 1;
			len[pos + 1] = 0;
		}
		if(pos > 1 && a[pos - 1] == 1){
			int aux = query(pos - 1);
			sumz += (len[aux] + len[pos])/2 - (len[aux]/2) - (len[pos])/2;
			update(1,1,n, pos, pos + len[pos] - 1, aux);
			len[aux] = len[aux] + len[pos];
			len[pos] = 0;
		}
	}
}

int main(){

	fastio;
	cin >> n >> m;

	frr(i, n){
		int x;
		cin >> x;
		where[x].pb(i);
	}

	build(1, 1, n);

	cnt = n;
	frr(k, m){
		if(where[k].size() == 0){
			cout << -1 << ' ';
			continue;
		}
		for(auto x: where[k]) upd(x, 0);
		print();
		for(auto x: where[k]) upd(x, -1);
	}
	gnl;


}
