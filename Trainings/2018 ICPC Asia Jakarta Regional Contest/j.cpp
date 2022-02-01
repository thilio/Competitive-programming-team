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
const int MAXN = 5e5 + 10;

int n, ans[MAXN][20];

vector<pair<string, int>> v;
vector<string> vv;



int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n;

	string s;
	fr(i, n){
		cin>>s;
		int m = s.size();

		for (int msk = 1; msk < (1<<m); msk++){
			string t;
			fr(j, m)
				if ((1<<j) & msk)
					t.pb(s[j]);
			v.pb({t, i});
		}
	}

	sort(all(v));

	int m = v.size();

	fr(i, 20)
		ans[m][i] = -INF;

	for (auto x : v){
		vv.pb(x.fst);
	}

	for (int i = m - 1; i >= 0; i--){
		fr(j, 20)
			ans[i][j] = ans[i + 1][j]; // propaguei a resposta

		int sz = v[i].fst.size(); // tamanho do pedaço	
		int str = v[i].snd; // string original

		if (str == n - 1){ // não preciso procurar
			ans[i][str] = max(ans[i][str], sz);
		}
		else{
			auto it = upper_bound(all(vv), v[i].fst); // primeiro cara maior
			if (it != vv.end()){
				int p = (int)(it - vv.begin());
				ans[i][str] = max(ans[i][str], ans[p][str + 1] + sz);
			}	
		}
	}	

	cout<<max(ans[0][0], -1)<<endl;
}