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
int dx[4] = {+1,-1,0,0};
int dy[4] = {0,0,+1,-1};
int grid[400][400];
int vis[400][400];
int h,l;

bool is(int i,int j){
	if(i >= 0 && i < h && j >=0 && j < l) return true;
	return false;
}

int dfs(int i,int j){
	vis[i][j] = 1;

	int ans = 1;

	fr(k,4){
		if(is(i + dx[k],j + dy[k]) && vis[i + dx[k]][j + dy[k]] == 0){
			if(grid[i + dx[k]][j + dy[k]] == grid[i][j]){
				ans += dfs(i + dx[k],j + dy[k]);
			}
		}
	}

	return ans;
}

int main(){

	fastio;

	cin >> h >> l;

	fr(i,h){
		fr(j,l) cin >> grid[i][j];
	}

	int ans = 40000;

	fr(i,h){
		fr(j,l){
			if(vis[i][j] == 0) ans = min(ans,dfs(i,j));
		}
	}

	cout << ans << endl;





}
