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

ll a[100100];
ll b[3];
ll c[3];

int main(){

	fastio;

	int n;
	cin >> n;

	frr(i,n) cin >> a[i];

	frr(i,n){
		ll x;
		cin >> x;
		b[i%3] += x;
	}

	frr(i,n){
		fr(j,3){
			c[(i + j)%3] += a[i]*b[j];
		}
	}

	cout << c[0] << ' ' << c[1] << ' ' << c[2] << endl;


}
