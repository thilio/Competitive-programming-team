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

vi h ;
vi v;
int n;
int mxh,mxv;

bool ok(int x){

	fr(i,n){
		if(h[i] + x > v[i]) return true;
		if(v[i] > h[i] + x) return false;
	}

	return true;

}

int main(){

	fastio;

	
	cin >> n;

	int mx = -1;

	fr(i,n){
		int a;
		cin >> a;
		h.pb(a);
		mx = max(a,mx);
	}

	mxh = mx;



	int k = -1;

	fr(i,n){
		int b;
		cin >> b;
		v.pb(b);
		k = max(k,b);
	}

	fr(i,1001){
		if(ok(i)){
			cout << i << endl;
			return 0;
		}
	}

}
