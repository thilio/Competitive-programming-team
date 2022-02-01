#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

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

const ll mod = 1e9 + 7;

ll n, k;

ll memo[150][150][150][3];

ll cnt[3];

ll pd(ll x, ll y, ll z, ll r){
	
	if (x + y + z == n){
		if ((x * (x - 1) + y * (y - 1) + z * (z + 1)) == 2 * k)
			return 1;
		return 0;
	}

	if (x * (x - 1) + y * (y - 1) + z * (z + 1) > 2 * k)
		return 0;

	ll &pdm = memo[x][y][z][r];
	if (pdm != -1)
		return pdm;

	ll nxt[3] = {z, y, x};

	nxt[r]++;
	pdm = (pd(nxt[2], nxt[1], nxt[0], r) * cnt[0]) % mod;
	nxt[r]--;
	nxt[(r + 1) % 3]++;	
	pdm = (pdm + ((pd(nxt[2], nxt[1], nxt[0], (r + 1) % 3) * cnt[1]) % mod) ) % mod;
	nxt[(r + 1) % 3]--;
	nxt[(r + 2) % 3]++;
	pdm = (pdm + ((pd(nxt[2], nxt[1], nxt[0], (r + 2) % 3) * cnt[2]) % mod) ) % mod;			

	return pdm;
}

void solve(){
	ll l, r;

	cin>>n>>k>>l>>r;

	fr(i, 150)
	fr(j, 150)
	fr(k, 150)
	fr(l, 3)
		memo[i][j][k][l] = -1;

	fr(i, 3)
		cnt[i] = (max<ll>(0, r - i + 1) + 2)/3 - (max<ll>(0, l - i) + 2)/3;

	cout<< pd(0, 0, 0, 0)<<endl;
}

int32_t main(){
	freopen("khoshaf.in", "r", stdin);
	fastio;
	int T;
	cin>>T;
	while (T--)
		solve();
}