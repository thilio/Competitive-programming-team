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

	ll v[10];
	fr(i, 6) cin >> v[i];
	sort(v, v + 6);

	ll r;
	r = min(v[1] - v[0], v[2] - v[1]);

	for(ll i = 1; i < 6; i++){
		if(v[i] != v[i-1] + r){
			cout << v[i-1] + r << endl;
			return 0;
		}
	}

	if(r < v[0]) cout << v[0] - r << endl;
	if(r != 0) cout << v[5] + r << endl;
}
