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

unsigned long long f(unsigned long long a, unsigned long long b){

	unsigned long long ans = 0;

	for(int n = 1; n <= 63; n++){
		for(int m = 1; m <= 63; m++){
			for(int run = 1; run <= 63; run++){
				if(((run + 1)/2)*n + (run/2)*m > 63) continue;
				unsigned long long build = 0;

				frr(i, run){
					if(i%2){
						fr(j, n){
							build = (build << 1);
							build++;
						}
					}
					else{
						fr(j,m){
							build = (build << 1);
						}
					}
				}

				if(run == 1 && m > 1) continue;
				if(build >= a && build <= b) ans++;
			}
		}
	}

	return ans;
}

int main(){

	fastio;

	unsigned long long a, b;
	cin >> a >> b;

	cout << f(a, b) << endl;

}
