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
pll inter[200200];
ll delta[200200];
ll acum_delta[200200];
ll n,h;

bool ok(int i, int m){
	int y = acum_delta[m - 1];
	y -= acum_delta[i-1];
	if(y < h) return  true;
	return false;
}

int start(int i){
	int l = i;
	int r = n;
	int best = -1;
	while(l <= r){
		int m = (l + r)/2;
		if(ok(i,m)){
			best = m;
			l = m + 1;
		}
		else r = m - 1;
	}

	return best;
}

int main(){
	fastio;
	cin >> n >> h;

	frr(i, n) cin >> inter[i].fst >> inter[i].snd;
	frr(i, n-1) delta[i] = inter[i + 1].fst - inter[i].snd;
	frr(i, n-1){
		acum_delta[i] = acum_delta[i - 1] + delta[i];
	}

	ll ans = h;

	for(int i = 1; i <= n; i++){
		int last = start(i);
		ans = max(ans, inter[last].snd - inter[i].fst + (h - (acum_delta[last - 1] - acum_delta[i-1])));
	}

	cout << ans << endl;



}
