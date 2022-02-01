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
typedef long double ld;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

long double p[6000][2];
vector<ll> v;
int n;

long double sum;

void dp(){
	if(n%2){
		p[1][0] = 1;
	}

	for(int i = 2; i <= n; i++){
		for(int j = 1; j <= i - 1; j++){
			p[j][1] = p[j][0]; 
		}

		if((n + i) %2 == 0){
			p[i][0] = 1;
		}
		else{
			for(int j = 1; j <= i; j++){
				p[j][0] = ((ld)(j - 1)/(ld)i)*p[j - 1][1];
				p[j][0] += ((ld)(i - j)/(ld)i)*p[j][1];
			}
		}
	}
}

int main(){

	fastio;

	cout << setprecision(12) << fixed;
	cin >> n;

	fr(i, n){
		ll x;
		cin >> x;
		sum += x;
		v.pb(x);
	}

	sort(all(v));

	dp();
	ld ans = 0;
	frr(i, n){
		ans += v[i - 1]*p[i][0];
	}

	cout << ans << ' ' << sum - ans << endl;



}
