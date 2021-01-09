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
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

ll n, m, c[MAXN], p[MAXN];

bool test(ll d){
	ll sum = 0;
	fr(i, n){
		sum += max(0ll, p[i] * d - c[i]);
		if (sum >= m)
			return true;
	}
	return false;
}

int32_t main(){
	fastio;

	cin>>n>>m;
	fr(i, n)
		cin>>p[i]>>c[i];

	ll ini, fim, meio, best;

	ini = 1;
	fim = best = 2e9;	

	while (ini <= fim){
		meio = (ini + fim)/2;

		if (test(meio)){
			fim = meio - 1;
			best = meio;
		}
		else
			ini = meio + 1;
	}

	cout<<best<<endl;
}