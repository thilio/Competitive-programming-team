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

int main(){

	fastio;

	int T;
	cin >> T;
	while(T--){
			int c[10];
			int a[10];
			frr(i,3) cin >> c[i];
			frr(i,5) cin >> a[i];

			frr(i,3) c[i] -= a[i];

			if(c[1] < 0 || c[2] < 0 || c[3] < 0){
				cout << "NO" << endl;
				continue;
			}

			a[4] = max(0, a[4] - c[1]);
			a[5] = max(0, a[5] - c[2]);

			if(a[4] + a[5] <= c[3]) cout << "YES" << endl;
			else cout << "NO" << endl;
	}

}
