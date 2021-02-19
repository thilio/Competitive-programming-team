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

vector<ll> start, en;
ll n;
ll p;

bool ok(ll m){
	ll ini, fim;
	ini = fim = 0;
	int seen = 0;
	int remove = 1;
	while(ini < n){
		while(fim < n && start[fim] <= en[ini] + m){
			seen++;
			fim++;
		}

		if(seen >= p) return true;

		if(ini != n){
			if(en[ini + 1] == en[ini]){
				remove++;
			}
			else{
				seen -= remove;
				remove = 1;
			}
		}
		ini++;
	}

	return false;

}


int main(){

	fastio;
	int T;
	cin >> T;
	int caso = 1;

	while(T--){
		cin >> n >> p;
		start.clear();
		en.clear();

		fr(i,n){
			ll x,y;
			cin >> x >> y;
			start.pb(x);
			en.pb(y);
		}

		sort(all(start));
		sort(all(en));

		ll l = 0;
		ll r = 1000000000;

		ll best = -1;
		while(l <= r){
			ll m =(l + r)/2;

			if(ok(m)){
				best = m;
				r = m - 1;
			}
			else{
				l = m + 1;
			}
		}

		cout << "Case "<<caso++<< ": ";
		cout << best << endl;
	}

}
