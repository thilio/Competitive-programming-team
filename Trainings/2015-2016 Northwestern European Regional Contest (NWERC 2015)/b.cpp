#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

int n, p;
int l[300], r[300];
pii inter[300][300];
ll dp[300][300];

vi id;
vi good;
vi bad;

bool comp_sz(int i, int j){
	return (r[i] - l[i] < r[j] - l[j]);
}

bool comp(int i, int j){
	if(l[i] == l[j]) return r[i] < r[j];
	return l[i] < l[j];
}

int main(){

	fastio;
	cin >> n >> p;
	fr(i,n){
		cin >> l[i] >> r[i];
		id.pb(i);
	}

	sort(all(id), comp_sz);

	for(int i = 0; i < n; i++){
		bool ok = false;
		for(int j = 0; j < i; j++){
			if(l[id[i]] <= l[id[j]] && r[id[j]] <= r[id[i]]) ok = true;
		}
		if(ok) good.pb(id[i]);
		else bad.pb(id[i]);
	}

	//dbg(good.size());

	sort(all(bad),comp);

	for(int i = 0 ; i < bad.size(); i++){
		inter[i][i] = mp(l[bad[i]], r[bad[i]]);
		for(int j = i + 1; j < bad.size(); j++){
			inter[i][j] = {max(inter[i][j - 1].fst,l[bad[j]]), min(inter[i][j - 1].snd, r[bad[j]])};
		}
	}

	fr(i,300) fr(j,300) dp[i][j] = -INF;

	dp[0][0] = 0;

	for(int i = 1; i <= bad.size(); i++){
		for(int j = 1; j <= p; j++){
			for(int k = 1; k <= i; k++){
				if(inter[k-1][i-1].fst < inter[k-1][i-1].snd){
					dp[i][j] = max(dp[i][j], dp[k - 1][j - 1] + inter[k - 1][i - 1].snd - inter[k - 1][i - 1].fst);	
				}
			}
		}
	}

	sort(all(good), comp_sz);

	
	ll res = 0;
	int at = good.size() - 1;
	ll val = 0;
	for(int g = p; g >= 0; g--){
		if(g == 0 && bad.size()) break;
		res = max(res, dp[bad.size()][g] + val);

		if(at >= 0) val += r[good[at]] - l[good[at]];
		else break;
		at--;
	}

	cout << res << endl;


}
