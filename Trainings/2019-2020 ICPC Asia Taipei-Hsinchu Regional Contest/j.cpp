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

vi test[20];
int n, m;

int feat[600];

int main(){

	fastio;

	int T;
	cin >> T;
	while(T--){
		cin >> n >> m;
		string s;
		fr(i, m){
			test[i].clear();
			cin >> s;
			fr(j, n){
				if(s[j] == '0') test[i].pb(0);
				else test[i].pb(1);
			}
		}

		

		int ans = m + 1;

		for(int mask = 0; mask < (1 << m); mask++){
			fr(i, n) feat[i] = 0;
			fr(j, m){
				if(mask & (1 << j)){
					fr(i, n) feat[i] |= test[j][i];
				}
			}
			bool ok = true;
			fr(i, n){
				ok &= feat[i];
			}
			if(ok){
				ans = min(ans, __builtin_popcount(mask));
			}
		}

		if(ans > m) ans = -1;

		cout << ans << endl;
	}

}
