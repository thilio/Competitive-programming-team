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

int main(){
	fastio;

	ll t;
	cin >> t;

	while(t--){
		pair<pii, pii> a, b;
		cin >> a.f.f >> a.f.s >> a.s.f >> a.s.s;
		cin >> b.f.f >> b.f.s >> b.s.f >> b.s.s;
		ll ans = max((a.s.f - a.f.f)*(a.s.s - a.f.s), (b.s.f - b.f.f)*(b.s.s - b.f.s));

		if(max(a.f.f, b.f.f) <= min(a.s.f, b.s.f) && max(a.f.s, b.f.s) <= min(a.s.s, b.s.s)){
			ll difx = min(a.s.f, b.s.f) - max(a.f.f, b.f.f), dify = min(a.s.s, b.s.s) - max(a.f.s, b.f.s);
			//cout << difx << " " << dify << endl;
			ans = max(ans, dify*(a.s.f - a.f.f + b.s.f - b.f.f - difx));
			ans = max(ans, difx*(a.s.s - a.f.s + b.s.s - b.f.s - dify));	
		}

		cout<< ans << endl;
	}
}
