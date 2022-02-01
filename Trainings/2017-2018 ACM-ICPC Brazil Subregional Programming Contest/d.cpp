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
const ll MAXN = 1e6 + 10;

ll factor(ll n){
	ll ans = 0;

	for (ll i = 2; i * i <= n; i++){
		if (n % i)
			continue;
		ans++;
		while (n % i == 0)
			n /= i;
	}

	if (n != 1)
		ans++;

	return ans;	
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	ll n;
	cin>>n;

	ll ans = factor(n);

	ll pwr = 1;
	fr(i, ans)
		pwr *= 2ll;

	ans = pwr - ans - 1;
	
	cout<<ans<<endl;	
}