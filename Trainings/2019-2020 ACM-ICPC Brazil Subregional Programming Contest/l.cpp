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

// Teorema de Lucas
// m, n na base 10
// p um primo
// m_10 = (a_ka_{k-1}...a_0)_p
// n_10 = (b_kb_{k-1}...b_0)_p // potencialmente contém zeros a esquerda
// m escolhe n = \produtorio_{i = 0}^k (a_i escolhe b_i) mod p
// para p = 2 resolvemos o problema, lembrando que 0 escolhe 1 = 0
// precisamos considerar somente as submáscaras de bits ligados em m

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	ll n;
	
	cin>>n;
	cout<<(1ll<<(__builtin_popcountll(n)))<<endl;
}