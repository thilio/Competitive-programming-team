#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define endl '\n'
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

int n, g;
int p[110];
int sum;

pii calc(int x){ // return val e pop count;
	pii ret = {0, 0};
	for(int i = 0; i < n; i++){
		if(x & (1ll << i)){
			ret.snd++;
			ret.fst += p[i];
		}
	}

	ret.fst = (ret.fst*100)/sum;

	return ret;
}

int calc_v(int x){ // return val;
	pii ret = {0, 0};
	for(int i = 0; i < n; i++){
		if(x & (1ll << i)){
			ret.fst += p[i];
		}
	}

	ret.fst = (ret.fst*100)/sum;

	return ret.fst;
}

int main(){

	fastio;

	cin >> n >> g;

	fr(i, n) cin >> p[i];
	fr(i, n) sum += p[i];


	vi ans;
	int mn = n + 1;
	for(int mask = 0; mask < (1 << n); mask++){
		pii a = calc(mask);
		if(a.fst < g) continue;
		if(a.snd < mn){
			mn = a.snd;
			ans.clear();
			ans.pb(mask);
		}
		else if(a.snd == mn){
			ans.pb(mask);
		}
	}

	cout << mn << ' ' << ans.size() << endl;

	for(auto x: ans){
		cout << calc_v(x);
		fr(i, n){
			if(x & (1 << i)){
				cout << ' ' << i + 1;
			}
		}
		gnl;
	}

}
