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

ll best[2010];

unordered_map<int,ll> memo;

int main(){

	fastio;

	ll n,s;

	cin >> n >> s;

	fr(i,n){
		ll x,y;
		cin >> x >> y;
		best[x] = max(best[x],y);
	}

	fr(i,2000){
		if (i != 0) best[i] = max(best[i], best[i -1]);
	}

	ll l = s;
	ll r = s;

	vi pre_all;
	pre_all.pb(s);

	fr(i,35){
		l = l/2 - 502;
		r = r/2 + 502;
		for(int j = max(0ll,l); j <= min(r,s); j++) pre_all.pb(j);
	}
	

	vi all;

	sort(all(pre_all));

	fr(i, pre_all.size()){
		if(i == 0){
			all.pb(pre_all[i]);
		}
		else{
			if(pre_all[i] == pre_all[i - 1]) continue;
			else all.pb(pre_all[i]);
		}
	}

	//dbg(all.size());

	fr(j,all.size()){
		ll x = all[j];
		ll& y =memo[x];
		y = best[min(x,1001ll)];
		for(int i = max(x/2 - 502, 1ll); i <= min(x/2 + 502,x - 1); i++){
			y = max(y, memo[i] + memo[x - i]);
		}
	}
	cout << memo[s] << endl;

}
