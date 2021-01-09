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
const int MAXN = 3e2 + 10;

ll n, k, m[MAXN][MAXN], flip[MAXN][MAXN];
long double bin[MAXN][MAXN];

long double fastxp(long double base, ll exp){
	long double ans = 1;
	while (exp){
		if (exp & 1)
			ans *= base;
		base = base * base;
		exp >>= 1;
	}
	return ans;
}

void solve(){
	cin>>n>>k;

	frr(i, n)
		frr(j, n)
			cin>>m[i][j];

	ll tot = 0;		
	for (ll i = 1; i <= n; i++)
		for (ll j = 1; j <= n; j++){
			flip[i][j] = i * j * (n + 1 - i) * (n + 1 - j); // quadrados que englobam i,j
			tot += (n + 1 - i) * (n + 1 - j); // total de quadrados
		}
	
	long double ans = 0, aux, a, b;

	for (ll i = 1; i <= n; i++)
		for (ll j = 1; j <= n; j++){
			aux = 0;
			a = ((long double) flip[i][j])/((long double) tot); // prob de flipar
			b = ((long double) tot - flip[i][j])/((long double) tot); // prob de não flipar

			for (ll l = !m[i][j]; l <= k; l += 2)
				aux += bin[k][l]*fastxp(a, l)*fastxp(b, k - l);
			ans += aux;
		}

	cout<<setprecision(5)<<fixed;
	cout<<ans<<endl;
}

int32_t main(){
	freopen("fetiera.in", "r", stdin);
	fastio;

	for (int k = 1; k < MAXN; k++){ // calcula binomio via triangulo de pascal
		bin[k - 1][0] = 1;
		for (int i = 0; i < k; i++)
			bin[k][i + 1] = bin[k - 1][i] + bin[k - 1][i + 1];
	}

	int T;
	cin>>T;
	while (T--)
		solve();
}