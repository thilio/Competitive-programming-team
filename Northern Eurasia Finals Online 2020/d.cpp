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
const int MAXN = 3e5 + 1;

int n;
vi adj[MAXN];
string mapa[MAXN];

int common(int i, int j){
	int ans = 0;
	fr(k, 8)
		ans += mapa[i][k] == mapa[j][k];
	return ans;	
}

int ans[MAXN], memo[MAXN][1<<8];

int status(int pos, int msk){
	for (auto x : adj[pos]){
		if ((msk & (1<<x)) == 0) // sends to losing position
			return true;	
	}
	return false;	
}

int solve(int pos, int msk){
	int &pdm = memo[pos][msk];
	if (pdm != -1)
		return pdm;
	int s = status(pos, msk);

	if (pos == 0) // end here
		pdm = s;
	else{
		msk = (msk<<1) + s; // new mask
		if (msk & (1<<8))
			msk -= 1<<8;

		pdm = solve(pos - 1, msk);
	}

	return pdm;
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n;

	fr(i, n)
		cin>>mapa[i];

	fr(i, n){
		for (int j = i + 1; j < min(n, i + 9); j++){
			if (common(i, j) >= j - i)
				adj[i].pb(j - i - 1);
		}
	}	

	memset(memo, -1, sizeof memo);

	ans[0] = 0; // the starting player loses
	for (int i = 1; i < n; i++){ // step
		int msk = (1<<8) - 2; // inexistent tiles are winning
		ans[i] = solve(i - 1, msk);
	}

	fr(i, n)
		cout<<(ans[i]? 1 : 2);
	gnl;
}