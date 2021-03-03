#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e6 + 10;

int nu, nm, nd;
vi vu, vm, vd;


int val[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int x;

	cin>>nu;
	fr(i, nu){
		cin>>x;
		vu.pb(x);
	}

	cin>>nm;
	fr(i, nm){
		cin>>x;
		vm.pb(x);
	}

	cin>>nd;
	fr(i, nd){
		cin>>x;
		vd.pb(x);
	}

	sort(all(vu));
	sort(all(vm));
	sort(all(vd));

	bitset<60100> mid, down;

	// pela esquerda

	int u, m, d;

	mid.reset();
	down.reset();

	u = 0;
	m = d = -1;

	ll ans = 0;

	while (u < nu){
		while (m < nm - 1 and vm[m + 1] < vu[u]){
			m++;
			if ((vu[u] - vm[m]) <= 30000)
				mid[2 * (vu[u] - vm[m])] = 1;
		}

		while (d < nd - 1 and vd[d + 1] < vu[u]){
			d++;
			if (vu[u] - vd[d] <= 60000)
			down[vu[u] - vd[d]] = 1;
		}

		ans += (mid & down).count();

		u++;
		if (u < nu){
			int dlt = vu[u] - vu[u - 1];
			mid <<= 2 * dlt;
			down <<= dlt; 
		}
	}

	// pela direita
	
	mid.reset();
	down.reset();

	u = nu - 1;;
	m = nm;
	d = nd;

	while (u >= 0){
		while (m > 0 and vm[m - 1] > vu[u]){
			m--;
			if ((vm[m] - vu[u]) <= 30000)
				mid[2 * (vm[m] - vu[u])] = 1;
		}

		while (d > 0 and vd[d - 1] > vu[u]){
			d--;
			if (vd[d] - vu[u] <= 60000)
				down[vd[d] - vu[u]] = 1;
		}

		ans += (mid & down).count();

		u--;
		if (u >= 0){
			int dlt = vu[u + 1] - vu[u];
			mid <<= 2 * dlt;
			down <<= dlt; 
		}
	}

	for (auto l : vu)
		val[l + 100000]++;
	for (auto l : vm)
		val[l + 100000]++;
	for (auto l : vd)
		val[l + 100000]++;
	fr(i, MAXN)
		if (val[i] == 3)
			ans++;

	cout<<ans<<endl;
}