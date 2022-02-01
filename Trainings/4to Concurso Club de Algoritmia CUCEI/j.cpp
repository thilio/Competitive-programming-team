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

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	ll n, k, m, memo[11234][10];

	cin>>n>>k>>m;

	for (int j = 0; j < m; j++)
		memo[n][j] = k;
	memo[n][m] = k - 1;

	for (int i = n - 1; i > 0; i--){
		for (int j = 0; j < m; j++)
			memo[i][j] = ((k - 1) * memo[i + 1][1] + memo[i + 1][j + 1]) % mod;
		memo[i][m] = ((k - 1) * memo[i + 1][1]) % mod;
	}

	cout<<memo[1][0]<<endl;
}