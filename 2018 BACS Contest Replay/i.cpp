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

ll impar(ll x){
	while(x%2 == 0) x/=2;
	return x;
}

ll a[MAXN];	

int main(){
	fastio;

	ll t;
	cin >> t;

	frr(ts, t){
		ll n;
		cin >> n;

		frr(i, n) cin >> a[i];

		ll sum = a[1], g = a[1];
		for(ll i = 2; i <= n; i++){
			sum += a[i];
			g = __gcd(a[i], g);
		}

		if(impar(sum) == impar(g)){
			cout << "Case " << ts << ": YES" << endl;
		}
		else{
			cout << "Case " << ts << ": NO 1" << endl;
		}
	}
}
