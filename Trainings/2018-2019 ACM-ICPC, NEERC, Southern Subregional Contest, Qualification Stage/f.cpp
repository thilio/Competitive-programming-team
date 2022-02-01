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

int tri[1000000][28];

int f(int v){
	int sum = 0;
	fr(i,6){
		if(i <= 2)
			sum += v%10;
		else
			sum -= v%10;
		v/=10;
	}
	return abs(sum);
}

int main(){

	fastio;
	int n;
	cin >> n;

	for(int i = 0; i < 1000000;i++){
		if(i != 0){
			fr(j,28) tri[i][j] = tri[i-1][j];
		}
		tri[i][f(i)]++;
	}

	fr(i,n){
		int x;
		cin >> x;

		int y = f(x);
		int ans = 0;
		fr(j,y) ans += tri[x][j];
		cout << ans << endl;
	}

}
