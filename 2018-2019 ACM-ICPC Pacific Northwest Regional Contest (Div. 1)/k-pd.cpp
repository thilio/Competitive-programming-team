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

int valor(int msk){
	int ans = 0;
	int cnt = 1;
	for (int i = 9; i >= 0; i--)
		if (msk & (1 << i)){
			ans += cnt*i;
			cnt *= 10;
		}
	return ans;	
}

int soma(int msk){
	int ans = 0;
	for (int i = 9; i >= 0; i--)
		if (msk & (1 << i)){
			ans += i;
		}
	return ans;	
}

bool valid(int n, int msk){
	return (n == (n | msk));	
}

int sng = 1; // -1 = max, 1 = min

long double memo[3000];

long double pd(int n){
	long double &pdm = memo[n];
	if (pdm != -1)
		return pdm;
	pdm = 0;
	long double best;
	bool ok;
	for (int d1 = 1; d1 <= 6; d1++){
		for (int d2 = 1; d2 <= 6; d2++){

			ok = 1;
			best = (sng == 1? llINF : -llINF);
			
			for (int msk = 1; msk < (1 << 10); msk++){

				if (valid(n, msk) and soma(msk) == d1 + d2){
					ok = 0;
					if (sng * best > sng * pd(n ^ msk))
						best = pd(n ^ msk);
				}

			}

			if (ok)
				best = valor(n);
		
			pdm += (1.0/36.0) * best;
		}
	}

	return pdm;
}

void solve(int n, int d1, int d2){

	long double best = (sng == 1? llINF : -llINF);
	int tira = -1;

	fr(i, 3000)
		memo[i] = -1;

	for (int msk = 1; msk < (1 << 10); msk++){
		if (valid(n, msk) and soma(msk) == d1 + d2){

			if (sng * best > sng * pd(n ^ msk)){
				best = pd(n ^ msk);
			
				tira = 0;
				int cnt = 1;
				for (int j = 9; j >= 0; j--)
					if (msk & (1 << j)){
						tira += j * cnt;
						cnt *= 10;
					}
			}
		}
	}

	if (tira == -1)
		best = valor(n);
	cout<<tira<<' '<<best<<endl;
}

int32_t main(){
	fastio;
	cout << setprecision(5)<<fixed;

	int n, d1, d2;

	cin>>n>>d1>>d2;

	int aux = n;
	n = 0;

	while (aux){
		if (aux % 10 != 0)
			n |= (1 << (aux % 10));
		aux /= 10;
	}

	sng = 1;
	solve(n, d1, d2);

	sng = -1;
	solve(n, d1, d2);
}