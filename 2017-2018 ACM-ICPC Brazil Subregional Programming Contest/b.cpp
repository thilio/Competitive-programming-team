#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e6 + 10;

int n, t, a, x, y, trn;

set<int> values;
vector<int> seq;

int pos[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>t>>a>>x>>y;
	int p;

	memset(pos, -1, sizeof pos);

	int msk = 0;
	fr(i, t){
		cin>>p;
		msk |= (1 << p);
	}

	int cnt = 0;
	int sum = 0;
	while (true){ // Pq não demora muito
		if (pos[sum] == -1)
			pos[sum] = cnt;
		if (cnt - pos[sum] >= y){
			cout<<pos[sum]<<' '<<cnt - 1<<endl;
			return 0;
		}

		sum = (sum + a) % x;
		
		int bit = a & msk;
		bit = __builtin_popcount(bit) % 2;
		a = a >> 1;
		a |= (bit<<(n - 1));
		
		cnt++;
	}
}