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
const int MAXN = 1e5 + 10;

int n, q, r[MAXN], c[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>q;

	frr(i, n){
		cin>>r[i];
		r[i] = r[i] % 2;
		r[i] += r[i - 1];
	}

	frr(i, n){
		cin>>c[i];
		c[i] = c[i] % 2;
		c[i] += c[i - 1];
	}


	int x1, x2, y1, y2;
	while (q--){
		cin>>x1>>y1>>x2>>y2;

		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);

		bool ok = 1;

		int sum = r[x2] - r[x1 - 1];

		if (0 < sum and sum < (x2 - x1 + 1))
			ok = 0;
		
		sum = c[y2] - c[y1 - 1];
		if (0 < sum and sum < (y2 - y1 + 1))
			ok = 0;

		cout<<(ok? "YES":"NO")<<endl;
	}
}