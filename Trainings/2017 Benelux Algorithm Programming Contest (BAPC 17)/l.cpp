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

map<string, int> mapa;

int n, cnt, from[MAXN], to[MAXN];
long double val[MAXN], memo[2 * MAXN];
bool got[MAXN];

int32_t main(){
	fastio;
	mapa["pink"] = 0;
	mapa["blue"] = 1;
	cnt = 2;

	cin>>n;
	string s;
	long double x;
	fr(i, n){
		cin>>s;
		if (!mapa.count(s))
			mapa[s] = cnt++;
		to[i] = mapa[s];
		
		cin>>s;
		if (!mapa.count(s))
			mapa[s] = cnt++;
		from[i] = mapa[s];

		cin>>x;
		val[i] = log(x);
	}

	got[0] = 1;
	for (int i = 1; i < cnt; i++)
		memo[i] = -llINF;

	fr(i, n){
		if (got[from[i]]){
			memo[to[i]] = max(memo[to[i]], memo[from[i]] + val[i]);
			got[to[i]] = 1;
		}
	}

	if (!got[1]){
		cout<<0<<endl;
		return 0;
	}

	cout<<setprecision(10)<<fixed;

	if (memo[1] >= 4){
		cout<<10<<endl;
	}
	else{
		long double ans = min(10.0L, exp(memo[1]));
		cout<<ans<<endl;
	}
}