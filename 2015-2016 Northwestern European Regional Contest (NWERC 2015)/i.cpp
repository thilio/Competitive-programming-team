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

string s;
ll n;

void solve(ll lv, ll lc, ll rc, ll llin, ll rlin){
	if (lv == n){
		cout<<lv<<' '<<lc<<' '<<llin<<endl;
		exit(0);
	}

	ll mc = (rc - lc + 1)/2;
	ll ml = (rlin - llin + 1)/2;

	if (s[lv] == '0')
		solve(lv + 1, lc, rc - mc, llin, rlin - ml);
	if (s[lv] == '1')
		solve(lv + 1, lc + mc, rc, llin, rlin - ml);
	if (s[lv] == '2')
		solve(lv + 1, lc, rc - mc, llin + ml, rlin);
	if (s[lv] == '3')
		solve(lv + 1, lc + mc, rc, llin + ml, rlin);
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>s;

	if (s.size() == 1){ // zoom 1
		if (s[0] == '0')
			cout<<1<<' '<<0<<' '<<0<<endl;
		if (s[0] == '1')
			cout<<1<<' '<<1<<' '<<0<<endl;
		if (s[0] == '2')
			cout<<1<<' '<<0<<' '<<1<<endl;
		if (s[0] == '3')	
			cout<<1<<' '<<1<<' '<<1<<endl;
		return 0;
	}

	n = s.size();
	ll pwr = 1;

	fr(i, n)
		pwr *= 2;
	
	solve(0, 0, pwr -1, 0, pwr - 1);	
}