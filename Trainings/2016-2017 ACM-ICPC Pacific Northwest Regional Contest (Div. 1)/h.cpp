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
const int MAXN = 2e5 + 10;

ll n, k, memo[MAXN];
vector<ll> st;
vector< pair<ll, ll> > v;

ll pd(ll pos){
	if (pos >= k)
		return 0;

	ll &pdm = memo[pos];
	if (pdm != -1)
		return pdm;
	
	pdm = pd(pos + 1);

	ll p = (int) (lower_bound(all(st), v[pos].snd + 1) - st.begin());

	pdm =  max(pdm, pd(p) + v[pos].snd - v[pos].fst + 1);

	return pdm;
}


int32_t main(){
	fastio;
	
	cin>>n>>k;

	ll a, b;
	fr(i, k){
		cin>>a>>b;
		v.pb({a, b});
	}

	sort(all(v));

	for (auto x : v){
		st.pb(x.fst);
	}

	memset(memo, -1, sizeof(memo));

	cout<<n - pd(0)<<endl;
}