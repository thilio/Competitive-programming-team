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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int n, m, d;
map<tuple<vi, vi, int>, long double> memo;

long double pd(vi a, vi b, int dmg){
	if (b[0] == m)
		return 1;

	if (dmg == d)
		return 0;

	if (memo.count({a, b, dmg}))
		return memo[{a, b, dmg}];

	long double &pdm = memo[{a, b, dmg}];
	pdm = 0;

	int alv = 0;
	frr(i, 6)
		alv += a[i] + b[i];

	frr(i, 6){
		if (a[i] != 0){
			a[i]--; a[i - 1]++;
			pdm += (a[i] + 1) * pd(a, b, dmg + 1);
			a[i]++; a[i - 1]--;
		}
		if (b[i] != 0){
			b[i]--; b[i - 1]++;
			pdm += (b[i] + 1) * pd(a, b, dmg + 1);
			b[i]++; b[i - 1]--;
		}
	}

	pdm /= (double)alv;	
	return pdm;
}


int32_t main(){
	fastio;
	cin>>n>>m>>d;

	vi a, b;
	a.resize(7);
	b.resize(7);

	int x;
	fr(i, n){
		cin>>x;
		a[x]++;
	}
	fr(i, m){
		cin>>x;
		b[x]++;
	}

	cout<<setprecision(9)<<fixed;
	cout<<pd(a, b, 0)<<endl;
}