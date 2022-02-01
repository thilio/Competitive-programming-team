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

int32_t main(){
	fastio;
	
	ll k, r, pwr[33];

	cin>>k>>r;

	pwr[0] = 1;
	frr(i, 30)
		pwr[i] = 2 * pwr[i - 1];

	ll n = pwr[k] - r;	

	long double ans = 0, sum;

	int i = 1;
	while (pwr[i] <= n + 1){
		sum = 1;
		for (ll j = 0; j < pwr[i] - 1; j++){
			sum *= (double)(n - j)/((double)(pwr[k] - j - 1));
		}

		ans += sum;
		i++;
	}	

	cout<<setprecision(5)<<fixed;
	cout<<ans<<endl;


}