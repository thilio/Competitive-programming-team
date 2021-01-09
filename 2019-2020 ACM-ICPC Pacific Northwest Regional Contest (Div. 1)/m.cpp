#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define endl '\n'
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
const int MAXN = 2e3 + 10;
const ll mod = 1e9+7;

int n, m, mapa[MAXN][MAXN];
int mx[4] = {1, -1, 0, 0};
int my[4] = {0, 0, 1, -1};

bool valid(int x, int y){
	if (x < 0 or y < 0)
		return false;
	if (x >= n or y >= m)
		return false;
	return mapa[x][y] == 0;
}

void dfs(int x, int y){
	mapa[x][y] = 1;
	fr(k, 4)
		if (valid(x + mx[k], y + my[k]))
			dfs(x + mx[k], y + my[k]);
}

int32_t main(){
	fastio;
		
	cin>>n>>m;
	
	string s;
	fr(i, n){
		cin>>s;
		fr(j, m){
			if (s[j] == '.')
				continue;
			if (s[j] == '/'){
				mapa[2 * i + 1][2 * j + 2] = 1;
				mapa[2 * i + 2][2 * j + 1] = 1;
			}
			else{
				mapa[2 * i + 1][2 * j + 1] = 1;
				mapa[2 * i + 2][2 * j + 2] = 1;	
			}				
		}
	}

	n = 2 * n + 2;
	m = 2 * m + 2;

	int ans = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (mapa[i][j])
				continue;
			ans++;
			dfs(i, j);
		}
	}	

	cout<<ans - 1<<endl;	
}