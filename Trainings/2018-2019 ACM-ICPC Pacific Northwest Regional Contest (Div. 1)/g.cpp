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
const int MAXN = 1e5 + 10;

ll sq(int x){ return x * x;}

int32_t main(){
	fastio;
	cout << setprecision(3)<<fixed;

	ll x, y, a, b, c, d;
	
	cin>>x>>y>>a>>b>>c>>d;

	if (a > c)
		swap(a, c);
	if (b > d)
		swap(b, d);

	ll ans = llINF;

	for (ll i = a; i <= c; i++)
		for (ll j = b; j <= d; j++)
			ans = min(ans, sq(x - i) + sq(y - j));
	cout<<sqrt(ans)<<endl;	
}