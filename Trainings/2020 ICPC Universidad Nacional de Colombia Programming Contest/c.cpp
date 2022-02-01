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
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 5e6 + 10;

const ll mod = 1e9 + 7;

ll a, k, ans[MAXN];

int32_t main(){
	fastio;

	cin>>a>>k;

	ll pwr = 1, sum = 0;

	frr(i, k){
		pwr = (pwr * a) % mod;
		ans[i] = (ans[i] + pwr) % mod;
		for (int j = 2 * i; j <= k; j += i)
			ans[j] = (ans[j] - ans[i] + mod) % mod;
		
		sum = (sum + ans[i]) % mod;
	}
	
	cout<<sum<<endl;
}