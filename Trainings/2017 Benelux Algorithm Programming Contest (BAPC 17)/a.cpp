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

const long double pi = acos(-1);

int32_t main(){
	fastio;
	int m, n;
	long double R, r;

	cin>>m>>n>>R;
	r = R/n;

	int a, b, c, d;
	cin>>a>>b>>c>>d;

	long double ans = 0;
	ans += abs(b - d) * r;
	
	b = min(b, d);
	d = min(b, d);

	int dlt = abs(a - c);

	if (2 * r > (pi * r * dlt)/m)
		ans += (pi * r * d * dlt)/m;	
	else
		ans += 2 * r * b;

	cout<<setprecision(12)<<ans<<endl;
}