#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(ll i = 0; i < n; i++)
#define frr(i, n) for(ll i = 1; i <= n; i++)
#define frm(i, n) for(ll i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<ll,ll> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

ll fastxp(ll n, ll e){
    if(e == 0) return 1;
    ll ans = fastxp(n, e/2);

    ans = (ans*ans)%MOD;

    if(e%2 == 1) ans *= n;

    return (ans)%MOD;
}
ll fat[110], fatInv[110];

ll bin(ll a, ll b){
	if(a < 0 || a < b) return 0;
	else {
		ll baixo = fatInv[b];
		baixo = (baixo * fatInv[a - b])%MOD;

		return (fat[a]*baixo)%MOD;
	}
}

ll dp[101][101][11];
ll fr[11];
string s;
ll n, np, ni;


ll solve(ll x){
	mem(dp, 0);
	dp[0][0][0] = 1;

	ll tot = 0;

	for(ll d = 0; d < 10; d++){
		ll f = fr[d];
		if(f == 0) continue;
		for(ll a = 0; a <= tot; a++){
			for(ll j = 0; j <= f; j++){
				for(ll r = 0; r < 11; r++){
					ll & aux = dp[a + j][tot - a + f - j][((r + j*d - (f - j)*d)%11 + 11)%11];
					aux = (aux + (bin(np - a, j)*bin(ni - (tot - a), f - j))%MOD*dp[a][tot-a][r])%MOD;

					/*
					if(a + j == 1 && tot - a + f - j == 2 && ((r + j*d - (f - j)*d)%11 + 11)%11 == 9){
						cout << "ola" << endl;
						cout << d << " " << bin(np - a, j) << " " << bin(ni - (tot - a), f - j) << " " << dp[a][tot - a][r] << endl;
						cout << a + j << " " << tot - a + f - j << ((r + j*d - (f - j)*d)%11 + 11)%11 << endl;
						cout << aux << endl;
					}
					*/
					
				}
			}
		}
		tot += f;
		
		/*
		cout << "---------------" << endl;
		fr(i, 4){
			fr(r, 11) cout << i << ' ' << r << " " << dp[i][tot - i][r] << endl;
		}
		cout << "---------------" << endl;
		*/	
	}

	if(np == ni) return dp[np][ni][x];
	else return dp[np][ni][11 - x];
}

int main(){
	fastio;
	fat[0] = 1;
	frr(i, 100) fat[i] = (fat[i-1]*i)%MOD;
	fatInv[0] = 1;
	frr(i, 100) fatInv[i] = fastxp(fat[i], MOD - 2);

	while(cin >> s){
		n = (ll)s.size();
		fr(i, 10) fr[i] = 0;
		fr(i, n) fr[s[i] - '0']++;
		if(n%2 == 0){
			ni = n/2;
			np = ni - 1;
		}
		else{
			ni = n/2;
			np = ni;
		}

		ll ans = 0;

		frr(i, 9){
			if(fr[i]){
				fr[i]--;
				ll aux = solve(i);
				//cout << aux << " " << i << endl;
				ans = (ans + aux)%MOD;

				fr[i]++;
			}
		}

		cout << ans << endl;
	}
}
