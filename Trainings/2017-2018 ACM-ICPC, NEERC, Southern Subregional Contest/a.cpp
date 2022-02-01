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

ll n, m, a, d, maxDPega;
ll v[MAXN];

void read(){
	cin >> n >> m >> a >> d;
	maxDPega = d/a + 1;
	frr(i, m) cin >> v[i];
	v[m+1] = 2*INF;
}

int main(){
	fastio;

	read();
	ll i = 1, tFecha = 0, itn = 1, ans = 0;

	while(itn <= n || i <= m){
		if(itn*a >= v[i]){
			tFecha = v[i] + d;
			while(i <= m && v[i] <= tFecha) i++;
			itn = tFecha/a + 1;
			ans++;
		}
		else{
			ll l = itn, r = v[i]/a;
			if(i == m + 1 || r > n) r = n;


			ans += max((r - l)/maxDPega + 1, (ll)1);  // 
			tFecha = r*a - ((r - l)%maxDPega)*a + d;
			while(i <= m && v[i] <= tFecha) i++;
			itn = tFecha/a + 1;
		}

		if(itn > n) itn = (2*INF)/a;
	}
	
	cout << ans << endl;
}
