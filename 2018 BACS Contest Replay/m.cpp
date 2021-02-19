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
int m,n, k;
ll c[20100], b[20100], a[20100];
int main(){

	fastio;

	int T;
	cin >> T;
	while(T--){
		cin >> m;
		m--;
		fr(i,m + 1) cin >> b[i];
		cin >> k;
		k--;
		fr(i,k + 1) cin >> c[i];

		n = k - m;

		for(int i = 0; i <= n; i++){
			ll sum = 0;
			for(int j = 1; j <= i; j++){
				if(m - j >= 0 && n - i + j >= 0) sum += b[m - j]*a[n - i + j];
			}
			a[n - i] = (c[m + n - i] - sum)/ b[m];
		}
		cout << n + 1 << endl;
		fr(i, n + 1){
			cout << a[i] << ' ';
		}
		gnl;

	}

}
