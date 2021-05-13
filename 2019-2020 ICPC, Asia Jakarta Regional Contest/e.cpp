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

int n, L, R, k;
int v[100100];

bool erro;

int memo[100100][2]; // 0 e min, 1 e max

void pd(){

	memo[n][0] = L;
	memo[n][1] = R;

	for(int i = n - 1; i >= 1; i--){
		if(v[i] == v[i + 1]){
			memo[i][0] = memo[i + 1][0];
			memo[i][1] = memo[i + 1][1];
		}
		else if(v[i] < v[i + 1]){
			memo[i][0] = max(L, memo[i + 1][0] - k);
			memo[i][1] = memo[i + 1][1] - 1; 
		}
		else{
			memo[i][0] = memo[i + 1][0] + 1;
			memo[i][1] = min(R, memo[i + 1][1] + k);
		}

		if(memo[i][0] > memo[i][1]) erro = true;
	}
}

void build(){
	vi ans;

	ans.pb(memo[1][0]);
	int at = memo[1][0];

	for(int i = 2; i <= n; i++){
		if(v[i] == v[i - 1]){
			ans.pb(at);
		}
		else if(v[i] > v[i - 1]){
			at = max(at + 1, memo[i][0]); 
			ans.pb(at);
		}
		else{
			at = max(at - k, memo[i][0]);
			ans.pb(at);
		}	
	}

	for(auto x: ans) cout << x << ' ';
	gnl;
}

int main(){

	fastio;

	cin >> n >> L >> R >> k;

	frr(i, n) cin >> v[i];

	pd();

	//for(int i = 1; i<= n; i++) cout << memo[i][1] << ' ';
	//	gnl;
	//for(int i = 1; i<= n; i++) cout << memo[i][0] << ' ';
	//	gnl;
	if(erro){
		cout << -1 << endl;
		return 0;
	}

	build();



}
