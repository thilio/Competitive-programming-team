#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;
const ll mod = 1e9 + 7;

ll n, sum[1ll<<17], v[64][10], tam[64];
ll memo[1<<16];

ll pd(int sense){
	memo[(1<<16) - 1] = 0;

	ll aux;
	for (int msk = (1<<16) - 2; msk >= 0; msk--){
		ll &pdm = memo[msk];
		pdm = (sense == 0? llINF : 0);

		for (int i = 0; i < 16; i++)
			if (!(msk&(1<<i))){
				aux = memo[msk|(1<<i)] + sum[msk|(1<<i)];
				if (sense == 0)
					pdm = min(pdm, aux);
				else
					pdm = max(pdm, aux);
		}
	}

	return memo[0];	
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	string read;
	cin>>read;

	n = stoll(read, 0, 16);

	fr(i, n){
		cin>>read;
		tam[i] = read.size();
		fr(j, read.size()){
			string xs(1, read[j]);
			v[i][j] = stoll(xs, 0, 16);
		}
	}
	
	for (int msk = 0; msk < (1<<16); msk++){
		fr(id, n){
			int sz = tam[id];
			ll pwr = 1;
			fr(i, sz){
				if (!(msk & (1<<v[id][sz - i - 1]))){
					sum[msk] += v[id][sz - i - 1] * pwr;
					pwr *= 16;
				}
			}	
		}
	}

	ll mn = pd(0);	
	ll mx = pd(1);

	ll fat[20];
	fat[0] = 1;

	frr(i, 17){
		fat[i] = (fat[i - 1] * ((ll)i));
		fat[i] = fat[i] - (fat[i] / mod) * mod;
	}

	ll ans = 0, aux;
	for (int msk = 1; msk < (1<<16); msk++){
		sum[msk] = sum[msk] - (sum[msk]/mod)*mod;
		aux = __builtin_popcount(msk);
		aux = (fat[aux] * fat[16 - aux]) % mod;
		aux = sum[msk] * aux;
		aux = aux - (aux/mod)*mod;
		ans += aux;
		ans = ans - (ans/mod)*mod;
		
	}

	cout<<hex<<mn<<' ';
	cout<<hex<<mx<<' ';
	cout<<hex<<ans<<endl;
}