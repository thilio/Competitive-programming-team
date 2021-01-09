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

int n, m, val[50], memo[1<<22];

int check(int msk){
	int sum = 0;
	for (int i = 0; i < n; i++)
		if (msk  & (1<<i))
			sum += val[i];
	return sum == 0;	
}

int pd(int msk){
	if (msk == 0)
		return 0;

	int &pdm = memo[msk];
	if (pdm != -1)
		return pdm;

	for (int i = 0; i < n; i++)
		if (msk & (1<<i))
			pdm = max(pdm, pd(msk ^ (1<<i)) + check(msk ^ (1<<i)));			
	return pdm;	
}

int32_t main(){
	fastio;

	cin>>n>>m;

	int a, b, c;
	fr(i, m){
		cin>>a>>b>>c;
		val[a] -= c;
		val[b] += c;
	}

	memset(memo, -1, sizeof(memo));

	cout<< n - pd((1 << n) - 1) <<endl;
}