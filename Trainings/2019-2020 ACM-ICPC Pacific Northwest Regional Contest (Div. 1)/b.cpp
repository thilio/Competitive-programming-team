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
const ll mod = 1e9+7;

int n, k, freq[MAXN], fa[MAXN], v[MAXN];
vi ans;
int32_t main(){
	fastio;

	cin>>n>>k;

	fr(i, n)
		cin>>v[i];

	fr(i, n)
		freq[v[i]]++;

	int aux;	

	for (int i = 0; i < n; i++){
		aux = v[i];

		if (fa[aux] == 1){
			freq[aux]--;
			continue;
		}
		
		int p = ans.size() - 1;

		while (p >= 0 and ans[p] >= aux and freq[ans[p]] > 0){
			fa[ans[p]] = 0;
			p--;
			ans.pop_back();
		}

		fa[aux] = 1;
		ans.pb(aux);

		freq[aux]--;
	}	

	for (auto x : ans)
		cout<<x<<' ';
	gnl;
}