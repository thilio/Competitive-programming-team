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
const int MAXN = 1e6 + 10;

int nxt[MAXN][30]; // proxima posição da letra


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	string s, t;
	int k;

	cin>>s>>k;

	int n = s.size();

	for (int i = 0; i < 30; i++)
		nxt[n][i] = n;

	for (int p = n - 1; p >= 0; p--){
		for (int i = 0; i < 30; i++)
			nxt[p][i] = nxt[p + 1][i];

		nxt[p][s[p] - 'a'] = p;
	}

	int p = 0, sz = 0;
	
	while (sz < k){
		for (int i = 0; i < 27; i++){
			if (nxt[p][i] + (k - sz) <= n){ // da pra pegar a menor letra e ir no guloso
				p = nxt[p][i];
				t.pb(s[p]);
				sz++;
				p++;
				break;				
			}
		}
	}

	cout<<t<<endl;
}