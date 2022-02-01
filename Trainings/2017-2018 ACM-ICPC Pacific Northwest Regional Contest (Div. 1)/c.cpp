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

ll pa_sum(ll a, ll r, ll n){
	return (n * (2 * a + r * (n - 1)))/2;
}

int32_t main(){
	fastio;
	ll a, b, sum = 0;
	cin>>a>>b;

	ll sq = 1;
	while ((sq + 1) * (sq + 1) <= b)
		sq++;

	for (ll x = 1; x <= sq; x++){
		sum += x * (b/x - (a - 1)/x);
		sum += pa_sum(max(sq, (a - 1)/x) + 1, 1, max(sq, b/x) - max(sq, (a - 1)/x));
	}

	cout<<sum<<endl;
}