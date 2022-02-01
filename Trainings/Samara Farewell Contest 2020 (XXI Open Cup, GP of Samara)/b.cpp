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

long double a[200200], b[200200], c[200200], d[200200];
int n;

bool ok(long  double r){
	long double sum = 0;

	fr(i, n){
		sum += max(b[i] - r*a[i], d[i] - r*c[i]);
	}

	if(sum >= 0) return true;
	return false;
}

int main(){

	fastio;

	cout << setprecision(15) << fixed;

	cin >> n;

	long double l = 0;
	long double r = INF;

	fr(i, n){
		cin >> a[i] >> b[i] >> c[i] >> d[i];
	}

	fr(i, 100){
		long double m = (l + r)/2;

		if(ok(m)) l = m;
		else r = m;
	}

	cout << l << endl;



}
