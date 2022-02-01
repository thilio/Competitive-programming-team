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

ll n,a,b;

long double f[1001000];
long double q;
bool termo;

void dp(){
	
	if(a == 0){
		termo = true;
		a++;
	}

	q = b - a + 1;

	f[0] = 0;
	frr(i,a) f[i] = 1;
	if(termo) f[1] = (q+1)/q;

	long double sum = f[1];

	for(int i = a + 1; i <= n; i++){
		f[i] = sum/q;
		if(termo) f[i] += (q+1)/q;
		else f[i] += 1;

		if (i - b > 0) sum -= f[i - b];
		sum += f[i - a + 1];
		 


	}

}
int main(){

	fastio;

	cout << setprecision(9) << fixed;

	cin >> n >> a >> b;

	dp();

	cout << f[n] << endl;


}
