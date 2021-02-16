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
const ll mod = 1e9 + 7;

ll bin[33][33], sum[33], memo[33][33], freq[33];

void pd(ll lim){ // bit atual x número de zeros que falta
	memset(memo, 0, sizeof memo);// quero formar numeros <= lim com zro zeros
	if (lim < 0)
		return;

	memo[0][1] = 1; // to no bit zero, posso colocar 1 zero e achar um numero menor ou igual

	if (lim%2)
		memo[0][0] = 1; // mesmo não colocando zero, acho numero menor ou igual

	for (int bit = 1; bit < 31; bit++)
		for (int zro = 0; zro < 31; zro++){
			if ((lim & (1 << bit))){ // bit ligado
				memo[bit][zro] = memo[bit - 1][zro]; // mantenho ligado
				if (zro > 0)
					memo[bit][zro] = (memo[bit][zro] + bin[bit][zro - 1]) % mod; // desligo e permuto o resto
			}
			else if (zro > 0)
				memo[bit][zro] = memo[bit - 1][zro - 1];
		}
	
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	for (int i = 0; i < 33; i++){ // calcula i escolhe j
		bin[i][0] = bin[i][i] = 1;

		for (int j = 1; j < i; j++)
			bin[i][j] = (bin[i - 1][j - 1] + bin[i - 1][j]) % mod;
	}

	int n;
	cin>>n;

	int op, l, r;
	ll x;
	while (n--){
		cin>>op>>l>>r;
		
		if (op == 0){
			cin>>x;

			pd(r - 1);
			for (int i = 0; i < 31; i++)
				freq[i] = memo[29][i]; // freq de numeros com leftness i <= r - 1

			pd(l - 1);
			for (int i = 0; i < 31; i++){ // freq de numeros com leftness l =< i <= r - 1
				freq[i] = (freq[i] - memo[29][i] + mod) % mod;
				sum[i] = (sum[i] + x * freq[i]) % mod; // soma desses valores para cada leftness
			}

		}
		else{
			ll ans = 0;
			for (int i = l; i < r; i++)
				ans = (ans + sum[i]) % mod;
			cout<<ans<<endl;
		}
	}
}