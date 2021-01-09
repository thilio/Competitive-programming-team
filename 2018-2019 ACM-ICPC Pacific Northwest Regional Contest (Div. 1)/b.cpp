#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const ll mod = 1e9 + 7;


const ll MAXN = 1e7;

ll lp[MAXN + 10];
vector<ll> pr;

void crivo(){
	for (ll i = 2; i <= MAXN; i++){
		if (lp[i] == 0){
			lp[i] = i;
			pr.pb(i);
		}
		for (ll j = 0; j < (ll)pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXN; j++)
      	  lp[i * pr[j]] = pr[j];
	}
}

vector< pair<ll, ll> > v;

int32_t main(){
	chapa;
	crivo(); // peguei todos os primos até 10**7
	chapa;

	ll pos;

	dbg(pr.size());
	gnl;

	for (ll p : pr){ // pego todos para inclusão exclusão
		pos = v.size();
		for (int i = 0; i < pos; i++){
			ll q = v[i].fst;
			if (q * p <= MAXN)
				v.pb({q * p, v[i].snd + 1});
		}
		v.pb({p, 1});
	}

	chapa;
	ll a, b, c, d;

	cin>>a>>b>>c>>d;	

	ll ans = (b - a + 1ll) * (d - c + 1ll);

	ll p, q;
	for (auto x : v){
		p = (b / x.fst) - (a / x.fst);
		q = (d / x.fst) - (c / x.fst);

		if (x.snd % 2ll)
			ans -= p * q;
		else
			ans += p * q;
	}

	cout<<ans<<endl;
}