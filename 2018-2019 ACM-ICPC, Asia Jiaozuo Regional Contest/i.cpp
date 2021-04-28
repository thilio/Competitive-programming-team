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

int n;
ll dist[100100];

ll dd(int l, int r){
	return dist[r] - dist[l];
}

int main(){

	fastio;

	int T;
	cin >> T;
	while(T--){
		cin >> n;
		dist[1] = 0;
		fr(i, n -1){
			ll a;
			cin >> a;
			dist[i + 2] = dist[i + 1] + a;
		}
		cout << 0 << ' ';
		ll ans = 0;
		ll sum = 0;
		for(int i = 2; i <= n; i++){
			if(i%2 == 0){
				sum += dd(i/2, n + 1 - i/2);
			}
			ans += sum;
			cout << ans;
			if(i != n) cout << ' ';
		}
		gnl;
	}

}
