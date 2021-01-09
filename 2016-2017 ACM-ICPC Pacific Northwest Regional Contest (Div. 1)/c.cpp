#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 2e5 + 10;

int v[MAXN], n, k, r;

int32_t main(){
	fastio;

	cin>>n>>k>>r;

	int x;
	fr(i, k){
		cin>>x;
		v[x]++;
	}

	int i, j, sum;
	sum = 0;

	i = j = 1;
	while (j <= r){
		sum += v[j];
		j++;
	}

	j--;

	int ans = 0;
	while (j <= n){
		if (sum < 2){
			for (int l = j; l > 0; l--){
				if (v[l] == 0){
					v[l] = 1;
					sum++;
					ans++;
				}
				if (sum >= 2)
					break;
			}
		}
		sum -= v[i++];
		sum += v[++j];
	}
	cout<<ans<<endl;
}