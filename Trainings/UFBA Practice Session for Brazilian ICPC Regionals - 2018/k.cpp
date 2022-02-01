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

ll acum[200200];
ll ans[200200];

int main(){

	fastio;

	int n;
	cin >> n;

	frr(i,n){
		if(i == 1){
			cin >> acum[i];
		}
		else{
			cin >> acum[i];
			acum[i] += acum[i-1];
		}
	}

	for(int i = n + 1; i <= 3*n; i++){
		acum[i] = acum[i-1];
	}

	for(int k = 1; k <= n; k++){
		int j = k;
		int i = 1;
		ll s = 0;
		while(j <= n){
			if(acum[j + 3*i - 1] - acum[j-1] > 0){
				s += acum[j + 3*i - 1] - acum[j-1];
			}
			j+= 3*i;
			i++;
		}

		ans[k] = s;
	}

	frr(i,n){
		cout << ans[i] << endl;
	}

}
