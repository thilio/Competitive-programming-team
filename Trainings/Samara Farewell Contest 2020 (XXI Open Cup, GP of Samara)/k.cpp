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

vii fi, se;

bool comp(pii a, pii b){
	if(a.snd == b.snd) return a.fst < b.fst;
	return a.snd > b.snd;
}

int main(){

	fastio;

	int T;
	cin >> T;
	while(T--){
		int n, m;
		cin >> n >> m;
		fi.clear();
		se.clear();
		fr(i, n){
			int t, h;
			cin >> t >> h;
			if(t <= h){
				fi.pb({t, h});
			}
			else{
				se.pb({t, h});
			}
		}

		sort(all(fi));
		sort(all(se), comp);

		int life = m;
		queue<int> pool;
		bool problem = false;

		for(auto x: fi){
			int t, h;
			tie(t, h) = x;

			while(life <= t - 1){
				t -= life - 1;
				if(pool.empty()){
					problem = true;
					break;
				}
				else{
					life = min(m, pool.front());
					pool.pop();
				}
			}

			life -= t - 1;
			pool.push(h);
			if(problem) break;
		}

		for(auto x: se){
			int t, h;
			tie(t, h) = x;

			while(life <= t - 1){
				t -= life - 1;
				if(pool.empty()){
					problem = true;
					break;
				}
				else{
					life = min(m, pool.front());
					pool.pop();
				}
			}

			life -= t - 1;
			pool.push(h);
			if(problem) break;
		}

		if(problem) cout << "NO" << endl;
		else cout << "YES" << endl;

	}

}
