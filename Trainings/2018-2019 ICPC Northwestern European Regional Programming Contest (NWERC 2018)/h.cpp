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

int n, c, b, ans[MAXN];
bool frz[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>c>>b;

	int x;
	fr(i, b){
		cin>>x;
		frz[x - 1] = 1;
	}

	int p = n - 1;

	while (c > 1){

		while (p >= 0 and frz[p])
			p--;

		ans[p] = 1;
		c -= 2;
		p -= 2;
	}

	if (c == 1)
		ans[0] = 1;

	fr(i, n)
		cout<<ans[i];
	gnl;
}