#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define endl '\n'
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

vi adj[110];
int vis[110];

string s[110];

bool comp(int i, int j){
	if(s[i].size() != s[j].size()) return false;

	int k = s[i].size();
	for(int p = 0; p < k; p++){
		int q = 0;
		while(q < k && s[i][q] == s[j][(p + q)%k]) q++;
		if(q == k) return true;
	}

	return false;
}

void dfs(int v){
	vis[v] = 1;

	for(auto x: adj[v]) if(!vis[x]) dfs(x);
}

int main(){

	fastio;

	int n;
	cin >> n;

	frr(i, n){
		cin >> s[i];
	}

	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			if(comp(i, j)){
				adj[i].pb(j);
				adj[j].pb(i);
			}
		}
	}

	int c = 0;

	frr(i, n){
		if(!vis[i]){
			dfs(i); c++;
		}
	}

	cout << c << endl;

}
