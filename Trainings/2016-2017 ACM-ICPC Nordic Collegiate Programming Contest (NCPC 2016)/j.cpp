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

int main(){

	fastio;

	int a, b;
	cin >> a >> b;

	if(a == b){
		cout << 0 << endl;
	}
	if(a < b){
		int ans1 = b - a;
		int ans2 = a + 360 - b;

		if(ans1 <= ans2) cout << ans1 << endl;
		else cout << -ans2 << endl; 
	}
	if(a > b){
		int ans1 = a - b;
		int ans2 = 360 - a + b;
		if(ans1 < ans2) cout << -ans1 << endl;
		else cout << ans2 << endl;
	}

}
