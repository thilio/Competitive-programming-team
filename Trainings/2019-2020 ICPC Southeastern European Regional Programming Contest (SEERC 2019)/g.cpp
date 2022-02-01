#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define frm(i, n) for(int i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));
#define db cout << "Debug" << endl;
#define all(x) begin(x), end(x)
#define dbg(x)  cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 110
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

int n, m, h, tot;
vector<array<int, 3>> ans[2];
char c[2][MAXN][MAXN];
vector<int> v[MAXN][2];

void buildMax(){
	fr(x, n) fr(y, m) fr(z, h){
		if(c[0][x][y] == '1' && c[1][x][z] == '1'){
			ans[1].pb({x, y, z});
		}
	}
}

void buildMin(int x){
	int l = 0, r = 1;
	if(v[x][0].size() > v[x][1].size()) swap(l, r);
	if(v[x][r].size() > 0 && v[x][l].size() == 0){
		cout << -1 << endl;
		exit (0);
	}
	if(v[x][r].size() == 0){
		return;
	}

	int it = 0;
	while(v[x][r].size() >= v[x][l].size() + it){
		if(l == 0) ans[0].pb({x, v[x][l][0], v[x][r][it]});
		else ans[0].pb({x, v[x][r][it], v[x][l][0]});
		it++;
	}
	it--;

	for(int i = 1; i < v[x][l].size(); i++){
		if(l == 0) ans[0].pb({x, v[x][l][i], v[x][r][it + i]});
		else ans[0].pb({x, v[x][r][it + i], v[x][l][i]});
	}
}

void read(){
	cin >> n >> m >> h;
	fr(i, n) fr(j, m) {
		cin >> c[0][i][j];
		if(c[0][i][j] == '1') v[i][0].pb(j);
	}
	fr(i, n) fr(j, h) {
		cin >> c[1][i][j];
		if(c[1][i][j] == '1') v[i][1].pb(j);
	}
}

int main(){
	fastio;
	read();
	fr(i, n) buildMin(i);
	buildMax();
	cout << ans[1].size() << "\n";
	for(auto x: ans[1]) cout << x[0] << " " << x[1] << " " << x[2] << "\n";

	cout << ans[0].size() << "\n";
	for(auto x: ans[0]) cout << x[0] << " " << x[1] << " " << x[2] << "\n";
}
