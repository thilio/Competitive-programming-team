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

int proxeq[1000100];
int proxma[1000100];
int prox[1000100];
int v[1000100];
int dp[1000100];
bool del[1000100];

map<int, int> m;

int main(){

	fastio;

	int n, k;
	cin >> n >> k;

	fr(i, n){
		cin >> v[i];
	}

	ms(proxeq, -1);
	ms(proxma, -1);
	ms(prox, -1);

	fr(i, n) dp[i] = INF;

	for(int i = n -1; i >= 0; i--){
		if(m.count(v[i])){
			proxeq[i] = m[v[i]];
		}
		if(m.count(v[i] + 1)){
			int x = v[i] + 1;
			proxma[i] = m[x];
		}
		m[v[i]] = i;
	}

	for(int i = n - 1;i>= 0; i--){
		if(proxeq[i] != -1){
			dp[i] = 1 + dp[proxeq[i]];
			prox[i] = proxeq[i]; 
			del[i] = true;
		}
		else{
			del[i] = true;
			dp[i] = 1;
			prox[i] = -1;
		}

		if(proxma[i] != -1){
			if(dp[proxma[i]] < dp[i]){
				del[i] = false;
				dp[i] = dp[proxma[i]];
				prox[i] = proxma[i]; 
			}
		}
		else if(v[i] != k){
			del[i] = false;
			dp[i] = 0;
			prox[i] = -1;
		}
	}

	//fr(i, n) cout << prox[i] << endl;

	fr(i, n){
		if(v[i] == 1){
			cout << dp[i] << endl;
			int j = i;
			while(j != -1){
				if(del[j]) cout << j + 1 << ' ';
				j = prox[j]; 
			}
			gnl;
			return 0;
		}
	}

	cout << 0 << endl;



}
