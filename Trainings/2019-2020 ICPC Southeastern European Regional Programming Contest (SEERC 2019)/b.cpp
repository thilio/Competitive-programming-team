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
const int MAXN = 5e2 + 10;

ll n, s1, s2;
ll x[MAXN], t[MAXN]; // nivel 0
ll y[MAXN], r[MAXN]; // nivel 1
ll memo[2][1101][511];

ll pd(){
	for (int exp1 = 0; exp1 <= 1100; exp1++)
		for (int exp2 = 0; exp2 <= 510; exp2++)
			memo[1][exp1][exp2] = llINF;

	memo[1][0][0] = 0;	

	for (int pos = 0; pos < n; pos++){
		for (int exp1 = 0; exp1 <= 1100; exp1++)
			for (int exp2 = 0; exp2 <= 510; exp2++){
				ll &pdm = memo[0][exp1][exp2];
				pdm = memo[1][exp1][exp2]; // propaga a resposta anterior

				if (exp1 - x[pos] >= 0 and exp1 - x[pos] < s1) // coloca no nivel 1
					pdm = min(pdm, t[pos] + memo[1][exp1 - x[pos]][exp2]);
				if (exp2 - y[pos] >= 0)
					pdm = min(pdm, r[pos] + memo[1][exp1][exp2 - y[pos]]);
			}		

		for (int exp1 = 0; exp1 <= 1100; exp1++)
			for (int exp2 = 0; exp2 <= 510; exp2++)
				memo[1][exp1][exp2] = memo[0][exp1][exp2];
	}

	ll ans = llINF;
	for (int exp1 = 0; exp1 <= 1100; exp1++)
		for (int exp2 = 0; exp2 <= 510; exp2++)
			if (exp1 >= s1 and (exp1 + exp2) >= s1 + s2)
				ans = min(ans, memo[0][exp1][exp2]);
	
	if (ans >= llINF)
		ans = -1;	

	return ans;		
}

vector< tuple<ll, ll, ll, ll> > in;


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>s1>>s2;

	ll a, b, c, d;
	fr(i, n){
		cin>>a>>b>>c>>d;
		in.pb({a, b, c, d});
	}

	sort(all(in));

	fr(i, n)
		tie(x[i], t[i], y[i], r[i]) = in[i];
	
	cout<<pd()<<endl;
}