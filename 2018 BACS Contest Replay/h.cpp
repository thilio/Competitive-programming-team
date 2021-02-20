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

ll dp[3000000];
int freq[200];
vi ans;
vi resp;
void pd(){
	// dp[mask] = # of derangements with fixed numbers in initial positions
	for(int mask = (1 << 20) - 1; mask >= 0; mask--){	
		int bits = __builtin_popcount(mask);
		if(bits == 20){
			dp[mask] = 1; //everyone is fixed
		}
		else{
			frr(i, 20){ // for all number try to fix it in the free position
				if(i != bits + 1){ // condition for derangements
					if((mask&(1 << (i - 1))) == 0){ // not used yet
						dp[mask] += dp[mask|(1 << (i - 1))]; // put it in the mask
					}
				}
			}
		}
	}

	dp[1] = 0; // just for consistency (we can't fix one in the first position), but this is not necessary
}

bool is(int mask, int j){ //true if and only if j is in the mask
	return (mask&(1 << (j - 1))) > 0;
}

void find(ll n, ll k){ // assuming n is small (<= 20) solve the problem
	int mask = 0;
	int x = 20;
	while(x != n){ // we fix the first numbers, if n = 18, i will fix 1 and 2 so i can look to derangements of 18 elements
		mask |= 1 << (20 - x);
		x--;
	}

	for(int i = 20 - n + 1; i <= 20; i++){ // for each position
		for(int j = 20 - n + 1; j <= 20; j++){ // can i put this number ?
			if(i == j) continue;
			if(is(mask,j)) continue;
			mask^= (1 << (j - 1));
			if(dp[mask] >= k){ // yes! this is the correct number
				ans.pb(j);
				mask |= (1 << (j - 1));
				break;
			}
			else{ // not enough deranregements
				k -= dp[mask];
				mask ^= (1 << (j - 1));
			}
		}
	}

	int mn = 110;
	for(auto x: ans) mn = min(x,mn); 
	fr(i,ans.size()) ans[i] -= mn - 1; // fix offset of line 62
}

int main(){

	fastio;

	pd();

	int T;
	cin >> T;
	while(T--){
		ans.clear();
		resp.clear();
		ms(freq,0);

		ll n,k;
		cin >> n >> k;
		if(n <= 20){
			find(n,k);
			fr(i,n) cout << ans[i] << ' ';
			gnl;
		}
		else{
			for(int i = 1; n - i >= 20; i+= 2){ // fix first elements, k is small enough so that only last 20 elements change
				resp.pb(i + 1);
				resp.pb(i);
			}
			int foi = resp.size(); // # of elements already selected

			int falta = n - resp.size();
			find(falta,k);

			fr(i,ans.size()) resp.pb(ans[i] + foi);
			fr(i,resp.size()) cout << resp[i] << ' ';
			gnl;
		}
	}

}
