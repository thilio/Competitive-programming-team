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

int n,d;
int v[200200];

bool ok(int k){

	int i = k + 1;
	int at = k + 1;

	while(i < n){
		if(v[i] <= at) at++;
		i++;
	}

	if(at >= d) return true;
	return false;
}

int main(){

	fastio;

	cin >> n >> d;

	fr(i,n) cin >> v[i];

	if(ok(-1)){
		cout << 0 << endl;
		return 0;
	}

	int l = 0;
	int r = n -1;

	int best = -1;

	while(l <= r){
		int m = (l + r)/2;
		if(ok(m)){
			best = m;
			r = m -1;
		}
		else l = m + 1;
	}

	//dbg(best);

	int ans = 0;
	int tem = 0;

	for(int i = 0; i <= best;i++){
		if(v[i] > tem){
			ans++;
			tem++;
		}
		else{
			tem++;
		}
	}

	cout << ans << endl;

}
