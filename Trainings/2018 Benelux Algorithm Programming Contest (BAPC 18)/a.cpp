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

vi aux;

int main(){

	fastio;
	ll n,x;
	cin >> n >> x;

	fr(i,n){
		ll a;
		cin >> a;
		aux.pb(a);
	}

	sort(all(aux));

	if(n == 1){
		cout << 1 << endl;
		return 0 ;
	}

	int t = 1;

	frr(i,n-1){
		if(aux[i] + aux[i-1] <= x)t++;
		else break;
	}

	cout << t << endl;


}
