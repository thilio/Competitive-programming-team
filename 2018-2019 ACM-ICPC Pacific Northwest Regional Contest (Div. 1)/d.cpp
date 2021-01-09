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


const ll mod = 1e9 + 9;

ll f[200][2000], c[200][2000];

int32_t main(){
	fastio;
	int k, b;

	cin>>k>>b;

	for (int i = 0; i <= b; i++){
		f[0][i] = c[0][i] = 0;
	}
	c[0][0] = 1;

	for (int i = 0; i < b; i++){
		for (int j = 0; j < k; j++){
			c[i + 1][(2 * j) % k] = (c[i + 1][(2 * j) % k] + c[i][j]) % mod;
			c[i + 1][(2 * j + 1) % k] = (c[i + 1][(2 * j + 1) % k] + c[i][j]) % mod;
			f[i + 1][(2 * j) % k] = ( f[i + 1][(2 * j) % k] + f[i][j]) % mod;
			f[i + 1][(2 * j + 1) % k] = (f[i + 1][(2 * j + 1) % k] + c[i][j] + f[i][j]) % mod;
		}
	}

	cout<<f[b][0]<<endl;
}