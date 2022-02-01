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
const int MAXN = 1e5 + 10;

ll n, k, agec, pric, agem, prim, t, d;
ll dftc[MAXN], dftm[MAXN], sobc[MAXN], sobm[MAXN], sobr[MAXN], a[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>k;
	cin>>agec>>pric>>agem>>prim;
	cin>>t>>d;

	frr(i, n)
		cin>>a[i];

	sort(a + 1, a + 1 + n);	// ordena por idade

	frr(i, n){
		sobr[i] = min(a[i] - 1, d);
		sobr[i] += sobr[i - 1];
	}


	for (int i = n; i > 0; i--){
		sobc[i] = max(min(a[i] - agec, d), 0ll); // o quanto ta sobrando
		sobm[i] = max(min(a[i] - agem, d), 0ll);
		
		sobc[i] += sobc[i + 1];	
		sobm[i] += sobm[i + 1];

		dftc[i] = min(min(a[i] - agec, d), 0ll); // o quanto ta faltando
		dftm[i] = min(min(a[i] - agem, d), 0ll);

		dftc[i] += dftc[i + 1];
		dftm[i] += dftm[i + 1];	
	}

	ll ans = -1;

	for (ll mto = n; mto >= 0; mto--){
		ll car = (n - mto + k - 1)/k;
	
		if (car > 0 and a[n - car + 1] + d < agec) // resposta invalida
			continue;
		if (mto > 0 and a[n - car - mto + 1] + d < agem)
			continue;

		ll fat = 0;
		ll sob = sobr[n - car - mto]; // sobra dos passageiros
	
		fat -= dftc[n - car + 1];
		sob += sobc[n - car + 1];

		fat -= (dftm[n - car - mto + 1] - dftm[n - car + 1]);
		sob += (sobm[n - car - mto + 1] - sobm[n - car + 1]);

		if (fat > sob) // falta idade
			continue;
			
		ll aux = mto * prim + car * pric + fat * t; // preço os carros e motos

		if (ans == -1)
			ans = aux;

		ans = min(ans, aux);
	}	

	cout<<ans<<endl;
}