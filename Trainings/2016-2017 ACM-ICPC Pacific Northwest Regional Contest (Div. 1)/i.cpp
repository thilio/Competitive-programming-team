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

vector<pll> pos;
vector<pll> neg;

ll n,k;

ll solve(){

	int p = pos.size() - 1;

	ll res = 0;
	ll sobrou = 0;
	while(p >= 0){
		pll aux = pos[p];
		if(aux.snd == 0){
			p--;
			continue;
		}

		res += 2*((aux.snd + k - 1)/k)*aux.fst;

		sobrou = ((aux.snd + k - 1)/k)*k - aux.snd;
		int j = p - 1;

		while(j >= 0 && sobrou > 0){
			ll x = min(sobrou,pos[j].snd);
			pos[j].snd -= x;
			sobrou -= x;
			j--;
		}

		p--;

	}

	return res;

}



int main(){

	fastio;
	cin >> n >> k;

	fr(i,n){
		ll a,b;

		cin >> a >> b;
		if(a < 0 ){
			neg.pb(mp(-a,b));
		}
		else{
			pos.pb(mp(a,b));
		}
	}

	sort(all(pos));
	sort(all(neg));

	ll ans = 0;

	ans += solve();

	//	dbg(ans);

	pos.clear();

	fr(i,neg.size()) pos.pb(mp(neg[i].fst,neg[i].snd));

	ans += solve();

	cout << ans << endl;





}
