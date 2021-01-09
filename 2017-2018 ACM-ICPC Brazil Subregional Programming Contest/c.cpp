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
	ll n, l;
	cin>>n>>l;

	ll a, b;
	cin>>a>>b;

	ll mmc = (a * b)/__gcd(a, b);

	fr(i, n - 2){
		cin>>a;
		mmc = (mmc * a)/__gcd(mmc, a);
	}

	ll ans = 1, mx = 1, aux;
	for (ll i = 1; i <= l; i++){
		aux = (mmc * i)/__gcd(mmc, i);

		if (aux > mx and aux <= l){
			mx = aux;
			ans = i;
		}
	}

	cout<<ans<<endl;
}