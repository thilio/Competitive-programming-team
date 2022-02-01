#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

int n,k;
double m;
int p[30][30];
int q[30][30];
int b[30];
int bc[1 << 21][22];
double memo[1 << 19][21][2];

double dp(){

	for(int mask = 0; mask < (1 << (n-1)); mask++){
		double val = bc[mask][n-1];
		for(int left = 0; left<= 20; left++){
			if(val >= 0){
				memo[mask][left][1] =  1;
				continue;
			}
			if(val <= -m){
				memo[mask][left][1] = 0;
				continue;
			}

			if(left == 0){
				memo[mask][left][1] = 1 + val/m;
			}
			if(left > 0){
				memo[mask][left][1] = 1 - (val*val)/(m*m);
			}

		}
	}

	
	for(int pos = n - 2; pos >= 0; pos--){
		for(int mask = 0; mask < (1 << pos); mask++){
			for(int left = 0; left <= 20; left++){
				double val = bc[mask][pos];

				//option 1, dont intervene
				double prob;
				double op1;
	
				if(val >= 0) prob = 1;
				else if (val <= -m) prob = 0;
				else prob = 1 + val/m;

				op1 = prob*memo[mask|(1<<pos)][left][1] + (1 - prob)*memo[mask][left][1];
				if(left == 0){
					memo[mask][left][0] = op1;
					continue;
				}

				//option 2, intervene and choose max
				double op2;

				if(val >= 0) prob = 1;
				else if (val <= -m) prob = 0;
				else prob = 1 - (val*val)/(m*m);

				op2 = prob*memo[mask|(1<<pos)][left - 1][1] + (1 - prob)*memo[mask][left - 1][1];

				//option 3, intervene and choose min
				double op3;

				if(val >= 0) prob = 1;
				else if (val <= -m) prob = 0;
				else prob = (1 + val/m)*(1 + val/m);

				op3 = prob*memo[mask|(1<<pos)][left - 1][1] + (1 - prob)*memo[mask][left - 1][1];

				memo[mask][left][0] = max(max(op1,op2),op3);
			}
		}

		for(int mask = 0; mask < (1 << pos); mask++){
			for(int left = 0; left <= 20; left++){
				memo[mask][left][1] = memo[mask][left][0];
			}
		}
	}
	
	return memo[0][k][0];


}

int main(){

	fastio;


	cout << setprecision(6) << fixed;
	cin >> n >> k >> m;

	fr(i,n){
		cin >> b[i];
		frr(j, n - i - 1) cin >> p[i][i + j];
		frr(j, n - i - 1) cin >> q[i][i + j];
	}

	for(int mask = 0; mask < (1 << n); mask++){
		fr(i,n){
			bc[mask][i] = b[i];
			for(int j = 0; j < i; j++){
				if(mask&(1 << j)) bc[mask][i] += p[j][i];
				else bc[mask][i] += q[j][i];
			}
		}
	}


	cout << dp() << endl;
}
