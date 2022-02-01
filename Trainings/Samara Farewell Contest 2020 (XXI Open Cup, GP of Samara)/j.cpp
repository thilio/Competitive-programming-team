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

int a[200200], b[200200];

int main(){

	fastio;

	int n;
	cin >> n;

	int ze = 0;

	ll sum = 0;

	fr(i, n){
		cin >> a[i] >> b[i];
		ze += (b[i] == 0);
		sum += a[i];
	}

	if(ze >= 2){
		int mx = -1;
		fr(i, n){
			if (b[i] != 0) mx = max(a[i] - b[i] + 1, mx);
			if(b[i] == 0) sum -= a[i];
		} 
		cout << mx <<' '<< sum <<  endl;
	}

	if(ze == 1){
		int mx = -1;
		fr(i, n){
			if(b[i] != 0) mx = max(a[i] - b[i] + 1, mx);
		} 
		cout << mx + 1 <<' ' << sum << endl;
	}

	if(ze == 0){
		vi v;
		fr(i, n) v.pb(a[i] - b[i]  + 1);

		sort(all(v));

		cout << min(v[n - 1], v[n - 2] + 1) << ' ' << sum << endl;
	}


}
