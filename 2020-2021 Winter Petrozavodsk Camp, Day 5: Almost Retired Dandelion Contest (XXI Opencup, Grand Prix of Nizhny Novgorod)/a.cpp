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

int m, n;
vi lista[12];
set<int> ans;

bool in[MAXN];

void solve(int msk){
	if (__builtin_popcount(msk) == m)
		return;

	fr(i, m)
		if ((msk&(1<<i)) == 0){
			
			int p = 0;
			while (in[lista[i][p]])
				p++;

			ans.insert(lista[i][p]);
			in[lista[i][p]] = 1;
			solve(msk|(1<<i));
			in[lista[i][p]] = 0;
		}
}


signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>m;

	fr(i, m){
		lista[i].resize(n);
		fr(j, n)
			cin>>lista[i][j];
	}

	solve(0);

	cout<<ans.size()<<endl;
	while (!ans.empty()){
		cout<<*ans.begin()<<' ';
		ans.erase(ans.begin());
	}
	gnl;
}	