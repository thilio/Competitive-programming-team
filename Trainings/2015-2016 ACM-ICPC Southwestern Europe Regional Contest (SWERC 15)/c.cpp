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

priority_queue<ll, vector<ll>, greater<ll> > pq;

int main(){

	fastio;

	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;

		ll ans = 0;

		frr(i, n){
			ll x;
			cin >> x;
			pq.push(x);
		}

		while((int)pq.size() != 1){
			ll a = pq.top();
			pq.pop();
			ll b = pq.top();
			pq.pop();

			ans += (a + b);

			pq.push(a + b);
		}

		pq.pop();
		cout << ans << endl;
	}

}
