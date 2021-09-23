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
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int a[3];

	fr(i, 3)
		cin>>a[i];

	int ans = a[0] + a[1] + a[2];
	int sum = ans;

	if (ans >= 500)
		ans -= 100;

	if (a[0] + a[1] >= 500 and a[2] >= 500)
		ans = min(ans, sum - 200);

	if (a[0] + a[2] >= 500 and a[1] >= 500)
		ans = min(ans, sum - 200);
	
	if (a[1] + a[2] >= 500 and a[0] >= 500)
		ans = min(ans, sum - 200);
	
	if (a[0] >= 500 and a[1] >= 500 and a[2] >= 500)
		ans = min(ans, sum - 300);

	cout<<ans<<endl;
}