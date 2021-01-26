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
vi v;
int n, k;

int t[700000];

void modify(int p, int value) {  // set value at position p
  for (t[p += n + 5] = value; p > 1; p >>= 1) 
  	t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // sum on interval [l, r)
  int res = 0;
  for (l += n + 5, r += n + 5; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res >= 1;
}


bool ok(int m){
	fr(i, 2 * n + 200)
		t[i] = 0;

	for(int i = n - 1; i>= 0; i--){
		auto it = upper_bound(all(v), v[i] + m);
		int pos = it - v.begin();
		pos--;

		if(pos < i + k - 1) 
			continue;

		if(pos >= n - 1){
			modify(i, 1);
		}
		else{
			bool q = query(i + k, pos + 2);
			if(q){
				modify(i, 1);
			}
		}
	}

	return query(0, 1);
}


int main(){

	fastio;
	cin >> n >> k;
	fr(i,n){
		int x;
		cin >> x;
		v.pb(x);
	}

	if (k == 1){
		cout<<0<<endl;
		return 0;
	}

	sort(all(v));

	int l = 0;
	int r = 1000*1000*1000;
	int best = -1;
	while(l <= r){
		int m = (l + r)/2;
		if(ok(m)){
			best = m;
			r = m - 1;
		}
		else{
			l = m + 1;
		}
	}

	cout << best << endl;
}
