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

const ll mod = 1e9 + 7;

ll t, m, n;

ll memo[55][MAXN];

ll pd(){
	n -= m - 1;

	for (int i = 0; i < n; i++)
		memo[1][i] = 1;

	for (int j = 2; j <= t; j++)
		for (int i = 0; i < n; i++){
			if (i == 0)
				memo[j][i] = memo[j - 1][1];
			else if (i == n - 1)
				memo[j][i] = memo[j - 1][i - 1];
			else
				memo[j][i] = (memo[j - 1][i - 1] + memo[j - 1][i + 1]) % mod;
		}		
	ll ans = 0;
	for (int i = 0; i < n; i++)
		ans = (ans + memo[t][i]) % mod;

	return ans;		
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>t>>m>>n;

	cout<<pd()<<endl;
}