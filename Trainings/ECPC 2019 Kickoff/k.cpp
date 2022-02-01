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

ll g[100100], h[100100];
pair<ll,ll> pass[100100];

ll teto(ll a,ll b){
	return (a + b - 1)/b;
}

int main(){

	freopen("plants.in","r",stdin);
	fastio;
	int n;
	cin >> n;
	fr(i,n) cin >> g[i];
	fr(i,n) cin >> h[i];

	fr(i,n - 1){
		if(h[i] == h[i + 1]){
			if(g[i] <= g[i + 1]) pass[i] = mp(0, llINF);
			else pass[i] = mp(-1,-1);
		}
		else{
			if(h[i] < h[i + 1]){				
				if(g[i] <= g[i + 1]) pass[i] = mp(0, llINF);
				if(g[i] > g[i + 1]) pass[i] = mp(teto(g[i] - g[i + 1], h[i+1] - h[i]), llINF);
			}
			else{
				if(g[i] > g[i + 1]) pass[i] = mp(-1,-1);
				if(g[i] == g[i + 1]) pass[i] = mp(0,0);
				if(g[i] < g[i + 1]) pass[i] = mp(0,(g[i+1] - g[i])/(h[i] - h[i + 1]));
			}
		}
	}

	fr(i,n-1){
		if(pass[i].fst == -1){
			cout << -1 << endl;
			return 0;
		}
	}

	ll ans = 0;
	fr(i,n - 1) ans = max(ans, pass[i].fst);

	fr(i,n - 1){
		if(ans > pass[i].snd) ans = -1;
	}

	cout << ans << endl;



}
