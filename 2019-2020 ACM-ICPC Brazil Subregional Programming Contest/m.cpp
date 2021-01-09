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
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int n, c, t, p[MAXN];

bool test(int val){
	int need = 1, now = 0;

	for (int i = 0; i < n; i++){
		if (p[i] > val) // saco maior que a capacidade
			return false;
		if (now + p[i] > val){
			need++; // mais um
			now = 0;
		}

		now += p[i];
	}

	return need <= c;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>n>>c>>t;

	fr(i, n)
		cin>>p[i];

	int ini, fim, meio, bst;
	ini = 1;
	bst = fim = 2e9;

	while (ini <= fim){
		meio = (ini + fim)/2;

		if (test(meio)){
			fim = meio - 1;
			bst = meio;
		}
		else
			ini = meio + 1;
	}

	cout<<((bst + t - 1)/t)<<endl;
}