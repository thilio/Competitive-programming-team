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

ll x, y, n, in[MAXN], out[MAXN], mn[MAXN], mx[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>x>>y>>n;

	memset(mn, -1, sizeof mn);
	memset(mx, -1, sizeof mx);

	ll a, b, sum = 0;
	fr(i, n){
		cin>>a>>b;
		
		if (mn[a] == -1)
			mn[a] = b;	
		else
			mn[a] = min(mn[a], b);

		mx[a] = max(mx[a], b);
	}

	ll down = 0;

	fr(i, y + 1){
		if (mx[i] != -1){
			in[mx[i]]++;

			out[mn[i]]++;
			sum += mn[i];
			down++;
		}
	}


	ll ans = llINF, up = 0, upsum = 0;

	for (ll p = y + 1; p >= 0; p--){
		if (in[p] > 0){
			up += in[p];
			upsum += in[p] * p;
		}

		if (out[p] > 0){
			down -= out[p];
			sum -= out[p] * p;
		}


		ll df = 2*((upsum - up * p) + (down * p - sum));

		ans = min(ans, df);
	}

	cout<<ans + x - 1<<endl;

}