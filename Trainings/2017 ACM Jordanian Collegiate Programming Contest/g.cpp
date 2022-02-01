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

int v[100100];
int seg[400400];
int n,tot;

void build(int node,int l,int r){
	if(l == r){
		seg[node] = v[l];
		return;
	}

	int m = (l + r)/2;

	build(2*node,l,m);
	build(2*node + 1,m+1,r);
	seg[node] = seg[2*node]|seg[2*node + 1];
}

int query(int node,int l,int r,int a,int b){
	if(a <= l && r <= b) return seg[node];
	if(r < a || l > b) return 0;

	int m = (l + r)/2;

	return query(2*node,l,m,a,b)|query(2*node + 1,m+1,r,a,b);
}

bool ok(int k){

	for(int i = 1; i + k - 1 <= n; i++){
		if(query(1,1,n,i,i + k - 1) <= tot) return true;
	}

	return false;
}

int main(){

	freopen("wifi.in", "r", stdin);
	fastio;

	int T;
	cin >> T;

	while(T--){
		
		cin >> n >> tot;

		frr(i,n){
			cin >> v[i];
		}

		build(1,1,n);

		int l = 1;
		int r = n;
		int best = 0;

		while(l <= r){
			int m = (l + r)/2;
			if(ok(m)){
				best = m;
				l = m + 1;
			}
			else r = m-1;
		}

		cout << best << endl;
		
	}

}
