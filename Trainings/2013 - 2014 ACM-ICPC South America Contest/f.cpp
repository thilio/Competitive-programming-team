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
int n,g;
vi lost;

int main(){

	fastio;
	while(cin >> n >> g){
		lost.clear();
		int draw = 0;
		int ans = 0;
		fr(i,n){
			int s;
			int r;
			cin >> s >> r;
			if(s > r) ans += 3;
			if(s == r){
				ans++;
				draw++;
			}
			if(s < r){
				lost.pb(r - s);
			}
		}

		if(g <= draw){
			ans += 2*g;
			cout << ans << endl;
			continue;
		}

		g-= draw;
		ans += 2*draw;

		sort(all(lost));

		for(auto x: lost){
			if(g < x) break;
			if(g == x){
				ans++;
				g = 0;
			}
			else{
				g -= x + 1;
				ans += 3;
			}
		}

		cout << ans << endl;
	}
}

