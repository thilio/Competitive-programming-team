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

ll v[50];
ll memo[MAXN];


ll pd(ll n, ll m){
	for (int j = 1; j <= m; j++)
		memo[j] = INF;
	memo[0] = 0;

	for (ll j = 0; j <= m; j++){
		if (memo[j] == INF)
			continue;
		for (ll i = 0; i < n; i++)
			if (j + v[i] <= m)
				memo[j + v[i]] = min(memo[j + v[i]], memo[j] + 1);
	}

	return memo[m];
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	ll m;

	cin>>m;

	v[0] = 1;
	ll n = 1;
	while (v[n - 1] * n <= m){
		v[n] = v[n - 1] * n;
		n++;
	}

	cout<<pd(n, m)<<endl;

}