#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	ll T, n, k, ans;

	cin>>T;
	while (T--){
		cin>>n>>k;
		ans = 0;
		bool par = 0, df;

		while (((k % 2) == par) and n > 1){
			ans += (n + (1 - par))/2;

			k = (k + par)/ 2;

			df = par;
			if (n % 2)
				par = par - 1;

			n = (n + df) / 2;
		}

		ans += (k + 1)/2;

		cout<<ans<<endl;
	}

}