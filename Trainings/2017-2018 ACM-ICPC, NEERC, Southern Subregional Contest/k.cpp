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

ll g[200200];
ll somal[200200];
ll somar[200200];
ll s[200200];

int main(){

	fastio;

	ll n;
	cin >> n;

	fr(i,n){
		cin >> g[i] >> s[i];
	}

	ll mx = INF;

	bool ok = false;

	fr(i,n){
		if(g[i] > mx) ok = true;

		somal[i] = min(mx - g[i], s[i]);
		mx = g[i] + somal[i] + 1;
	}

	mx = INF;

	for(int i = n - 1; i >= 0; i--){
		if(g[i] > mx) ok = true;
		somar[i] = min(s[i], mx - g[i]);
		mx = g[i] + somar[i] + 1;
	}

	if(ok) cout << -1 << endl;
	else{
		ll area = 0;

		fr(i,n){
			area += min(somar[i],somal[i]);
			g[i] += min(somar[i],somal[i]);
		}

		cout << area << endl;

		fr(i,n){
			cout << g[i] << ' ';
		}
		gnl;
	}


}