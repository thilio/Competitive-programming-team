#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
//#define endl '\n'
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

map<ll, int> M;
map<ll, int> aux;
vector<vector<ll>> v;
vector<ll> a;
int n;

bool tent(ll m){
	if(m == 0) return false;
	aux = M;

	ll k = 1;

	fr(i, n){
		if(aux[k] == 0) return false;
		aux[k]--;

		k = (2*k)%m;
	}

	return true;
}

int main(){

	fastio;

	//int n;

	cin >> n;

	fr(i, n){
		ll x;
		cin >> x;
		M[x]++;
		a.pb(x);
	}

	sort(all(a));

	if(n <= 60 && M[1ll << (n - 1)]){
		cout << (1ll << (n - 1)) + 1 << endl;
		return 0;
	}

	if(a[n - 1] == 0){
		cout << 1 << endl;
		return 0;
	}

	aux = M;

	for(auto x: a){
		while(aux[x] > 0){
			vector<ll> b;
			ll t = x;
			while(aux[t]){
				aux[t]--;
				b.pb(t);
				t *= 2;
			}
			v.pb(b);
		}
	}

	ll min_ini = 1e18 + 1;

	vector<ll> fim;

	for(auto vv : v){
		fim.pb(vv.back());
		if(vv[0] != 1 || M[1] > 1) min_ini = min(vv[0], min_ini);
	}

	sort(all(fim));

	int t = 0;

	for(auto x: fim){
		assert(t < 2);
		if(tent(2*x - min_ini)){
			cout << 2*x - min_ini << endl;
			return 0;
		}
		t++;
	}





}
