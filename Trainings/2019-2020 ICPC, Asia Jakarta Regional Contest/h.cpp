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

vector<pll> v;

int main(){

	fastio;

	int n;

	cin >> n;

	fr(i, n){
		ll x,y;
		cin >> x >> y;
		if(x < y) swap(x, y);
		v.pb({x, y});
	}

	sort(all(v));

	long long ans = 0;

	fr(i, n){
		ans = max(ans, v[i].fst*v[i].snd);
	}

	long long tent = 0;

	ll mx = -1;

	for(int i = n - 1; i >= 0; i--){
		if(i == n -1){
			mx = v[i].snd;
			continue;
		}
		else{
			tent = max(tent, v[i].fst*(min(mx, v[i].snd)));
			mx = max(mx, v[i].snd);
		}
	}

	tent*= 2;

	ans = max(ans, tent);

	cout << ans/2;
	if(ans&1) cout << ".5";
	else cout << ".0";
	gnl;



}
