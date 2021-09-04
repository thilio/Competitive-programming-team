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
const int MAXN = 1<<22;

int n, v[MAXN], a[MAXN], memo[MAXN];

void sos(){
	for (int msk = 0; msk <(1<<22); msk++)
		memo[msk] = a[msk]; // eu produzo essa representaçao

	for (int i = 0; i < 22; i++)
		for (int msk = 0; msk < (1<<22); msk++)
			if ((msk & (1<<i)))
				memo[msk] += memo[msk^(1<<i)];
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin>>T;

	while (T--){
		cin>>n;

		fr(i, n)
			cin>>v[i];
		fr(i, n)
			a[v[i]]++;

		sos();

		ll ans = 0;
		fr(i, n)
			ans += memo[v[i]];	

		fr(i, n){
			a[v[i]] = 0;
			v[i] = 0;
		}


		cout<<ans<<endl;
	}
}