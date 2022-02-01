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

int v[5050];

bool valid(int a,int b,int c){
	if(a <= b && b <= c) return false;
	if(a >= b && b >= c) return false;

	return true;
}

int main(){

	fastio;
	int n;
	cin >> n;

	frr(i,n){
		cin >> v[i];
	}

	int ans = 2;
	int tent = 2;
	int j = 1;

	while(j < n - 1){
		if(valid(v[j],v[j+1],v[j+2])){
			tent++;
			if(tent > ans) ans = tent;
			j++;
		}
		else{
			tent = 2;
			j++;
		}
	}

	cout << ans << endl;


}
