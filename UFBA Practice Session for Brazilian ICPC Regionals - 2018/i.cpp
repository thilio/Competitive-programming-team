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

int h[100100];
int seg[400400];

void update(int node,int l,int r,int j,int val){
	if(j < l || j > r) return;
	if(l == r && j == l){
		h[j] = val;
		seg[node] = 0;
		return;
	}

	int m = (l + r)/2;
	update(2*node,l,m,j,val);
	update(2*node + 1,m + 1,r,j,val);

	seg[node] = max(seg[2*node],seg[2*node + 1]);
	seg[node] = max(seg[node], abs(h[m+1] - h[m]));
}

int query(int node,int l,int r,int a,int b){
	if(r < a || l > b) return -1;
	if(a <= l && r <= b) return seg[node];

	int m = (l + r)/2;
	int ans1 = query(2*node,l,m,a,b);
	int ans2 = query(2*node + 1,m + 1,r,a,b);

//	dbg(ans1);dbg(ans2);

	int ans = max(ans1,ans2);
	if(ans1 != -1 && ans2 != -1) ans = max(ans,abs(h[m+1] - h[m]));

	return ans;
}

int main(){

	fastio;
	int n,k;
	cin >> n >> k;

	frr(i,n){
		cin >> h[i];
		update(1,1,n,i,h[i]);
	}

	//dbg(query(1,1,n,2,3));

	//return 0;

	fr(j,k){
		int op,i,hei;
		cin >> op >> i >> hei;

		if(op == 1) update(1,1,n,i,hei);
		else{
			int l = i;
			int r = n;

			int up;

			while(l <= r){
				int m = (l + r)/2;
				
				if(query(1,1,n,i,m) <= hei){
					l = m+1;
					up = m;
				}
				else{
					r = m - 1;
				}
			}
		//	dbg(up);
			r = i;
			l = 1;

			int down;
			while(l <= r){
				int m = (l + r)/2;
				if(query(1,1,n,m,i) <= hei){
					r = m - 1;
					down = m;
				}
				else{
					l = m + 1;
				}
			}

		//	dbg(down);

			cout << up - down + 1 << endl;
		}
	}

}
