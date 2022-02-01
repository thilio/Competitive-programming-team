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

int r, c;
int mat[200][200];
int comp[200][200];
ll ans = 5;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool is(int i, int j){
	if(i < 1 || i > r || j < 1 || j > c) return false;
	return true;
}

void dfs(int i, int j, int color){
	comp[i][j] = color;
	fr(k, 4){
		if(is(i + dy[k], j + dx[k]) && comp[i + dy[k]][j + dx[k]] == 0 && mat[i][j] == mat[i + dy[k]][j + dx[k]])	
			dfs(i + dy[k], j + dx[k], color);
	}
}

void transpose(){
	int cmat[200][200];

	frr(i, r) frr(j, c) cmat[i][j] = mat[i][j];

	frr(i, r) frr(j, c) mat[j][i] = cmat[i][j];

	swap(r, c);
}


int main(){

	fastio;

	cin >> r >> c;

	frr(i, r){
		frr(j, c) cin >> mat[i][j];
	}

	int color = 0;
	frr(i, r){
		frr(j, c){
			if(comp[i][j] == 0){
				color++;
				dfs(i, j, color);
			}
		}
	}
	ans += color;

	frr(i, r){
		frr(j, c - 1){
			if(mat[i][j] == mat[i][j + 1]) continue;
			if(mat[i][j] > mat[i][j + 1]){
				if(mat[i - 1][j] <= mat[i - 1][j + 1]) ans++;
				else{
					if(mat[i - 1][j + 1] >= mat[i][j] || mat[i - 1][j] <= mat[i][j + 1]) ans++;
				}
			}
			if(mat[i][j] < mat[i][j + 1]){
				if(mat[i - 1][j] >= mat[i - 1][j + 1]) ans++;
				else{
					if(mat[i - 1][j + 1] <= mat[i][j] || mat[i - 1][j] >= mat[i][j + 1]) ans++;
				}
			}
		}
	}

	transpose();
	frr(i, r){
		frr(j, c - 1){
			if(mat[i][j] == mat[i][j + 1]) continue;
			if(mat[i][j] > mat[i][j + 1]){
				if(mat[i - 1][j] <= mat[i - 1][j + 1]) ans++;
				else{
					if(mat[i - 1][j + 1] >= mat[i][j] || mat[i - 1][j] <= mat[i][j + 1]) ans++;
				}
			}
			if(mat[i][j] < mat[i][j + 1]){
				if(mat[i - 1][j] >= mat[i - 1][j + 1]) ans++;
				else{
					if(mat[i - 1][j + 1] <= mat[i][j] || mat[i - 1][j] >= mat[i][j + 1]) ans++;
				}
			}
		}
	}


	cout << ans << endl;
}
