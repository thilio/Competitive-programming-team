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
#define endl '\n'

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 128;

int n, m;
string letra[30];
string s;

int dp[100100];
bool two[100100];

bool tent(int i, int j){
	if(i + letra[j].size() > n) return false;

	for(int k = 0; k < letra[j].size(); k++){
		if(letra[j][k] != s[i + k]) return false;
	}

	return true;
}

int pd(int i){
	if(i == n){
		dp[i] = 1;
		return 1;
	}
	int& pdm = dp[i];
	if(pdm != -1) return pdm;

	pdm = 0;

	bool ok = false;
	int y = 0;
	fr(j, m){
		if(tent(i, j)){ 
			pdm += pd(i + letra[j].size());
			pdm %= MOD;
			if(two[i + letra[j].size()]) ok = true;
			if(dp[i + letra[j].size()] > 0) y++;
		}
	}
	if(y >= 2) ok = true;
	two[i] = ok;

	return pdm;
}

int main(){

	fastio;

	int T;
	cin >> T;

	while(T--){
		cin >> n >> m;
		char c;
		fr(i, m){
			cin >> c >> letra[i];
		}

		fr(i, n + 1){
			dp[i] = -1;
			two[i] = false;
		}

		cin >> s;
		pd(0);

		//fr(i, n + 1) dbg(dp[i]);

		if(two[0]){
			cout << "puppymousecat " << dp[0] << endl;
		}
		else if(dp[0] > 0){
			cout << "happymorsecode" << endl;
		}
		else{
			cout << "nonono" << endl;
		}

	}


}
