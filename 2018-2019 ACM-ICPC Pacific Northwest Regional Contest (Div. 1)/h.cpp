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
const int MAXN = 1e6 + 10;
const ll mod = 1e9 + 7;

int lp[MAXN];
vector<int> pr;

void crivo(){
	for (int i = 2; i <= MAXN; i++){
		if (lp[i] == 0){
			lp[i] = i;
			pr.pb(i);
		}
		for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i*pr[j] <= MAXN; j++)
      	  lp[i * pr[j]] = pr[j];
	}
}


int32_t main(){
	fastio;
	int n;

	cin>>n;
	if (n == 4){
		cout<<1<<endl;
		return 0;
	}

	crivo();
	
	int ans = 0, x;
	while (n > 4){
		for (int i = 1; i < pr.size(); i++){ // pula o 2
			x = pr[i];

			if (lp[n - x] == n - x){
				ans++;
				n = abs(n - 2 * x);
				break;
			}
		}
	}

	if (n == 4)
		ans++;

	cout<<ans<<endl;
	
}