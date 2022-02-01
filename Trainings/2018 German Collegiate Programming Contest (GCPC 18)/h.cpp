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
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

__int128 fast_xp(__int128 base, __int128 exp){
	__int128 ans = 1;
	while (exp){
		if (exp & 1)
			ans = (ans * base);
		base = base * base;
		exp /= 2;
	}
	return ans;
}

int32_t main(){
	fastio;
	ll m;
	cin>>m;

	for (ll n = 2; n < 54; n++){//2**54 > 1e16
		__int128 dlt = m;
		ll i = 1, aux;
		
		// if (n > 4)
		// 	return 0;

		while (dlt > 0){
			aux = fast_xp(i, n);
			dlt -= aux;
			i++;
			// dbg((ll)dlt);
		}

		if (dlt == 0){
			cout<<n + 1<<' '<<i - 1<<endl;
			return 0;
		}
	}

	cout<<"impossible"<<endl;
}