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
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

char m[30][30];
int n;
pii corBranco = {-1, -1};
vector<pii> brancas;

vector<pii> adj[30][30];

bool valid(int x, int y){
	if(x >= 1 && x <= n && y >= 1 && y <= n && m[x][y] != 'B') return 1;
	else return 0;
}

bool solve(int x, int y){
	frr(i, n) frr(j, n) adj[i][j].clear();

	int corDavez = (x + y)%4;
	m[x][y] = '_';

	for(auto davez: brancas){
		int r = davez.f, c = davez.s;
		if((r + 1 + c + 1)%4 == corDavez && valid(r + 1, c + 1) && valid(r - 1, c - 1)) {
			adj[r-1][c-1].pb({r + 1, c + 1});
			adj[r+1][c+1].pb({r - 1, c - 1});
		}
		if((r + 1 + c - 1)%4 == corDavez && valid(r + 1, c - 1) && valid(r - 1, c + 1)) {
			adj[r+1][c-1].pb({r - 1, c + 1});
			adj[r-1][c+1].pb({r + 1, c - 1});
		}
	}

	/*
	if(valid(x + 2, y + 2)) adj[x][y].pb({x + 2, y + 2});
	if(valid(x - 2, y + 2)) adj[x][y].pb({x - 2, y + 2});
	if(valid(x + 2, y - 2)) adj[x][y].pb({x + 2, y - 2});
	if(valid(x - 2, y - 2)) adj[x][y].pb({x - 2, y - 2});
	*/
	m[x][y] = 'B';

	/*
	if(y == 4 && x == 9){
		frr(i, n) {
			frr(j, n) cout << adj[i][j].size() << ' ';
			cout << endl;
		}
	}
	*/

	if(adj[x][y].size()%2 == 0) {
		int odd = 0;
		int soma = 0;
		frr(i, n) frr(j, n) {
			odd += adj[i][j].size()%2;
			soma += adj[i][j].size();
		}
		//cout << soma << " " << brancas.size() << endl;

		if(odd == 0 && (soma == 2*brancas.size())) return 1;
		else return 0;

	}
	else{
		int odd = 0;
		int soma = 0;
		frr(i, n) frr(j, n) {
			odd += adj[i][j].size()%2;
			soma += adj[i][j].size();
		}

		if(odd != 2 || (soma != 2*brancas.size())) return 0;
		else return 1;
	}
}

void read(){
	cin >> n;
	frr(i, n) frr(j, n) {
		cin >> m[i][j];
		if(m[i][j] == 'W'){
			if(corBranco == mp(-1, -1)) corBranco = {i, j};
			else if((corBranco.f - i)%2 != 0 || (corBranco.s - j)%2 != 0){
				cout << "None" << endl;
				exit (0);
			} 

			brancas.pb({i, j});
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	read();
	vector<pii> ans;
	frr(i, n) frr(j, n){
		if(m[i][j] == 'B' && ((corBranco.f - i)%2 != 0 || (corBranco.s - j)%2 != 0)) {
			//cout << corBranco.f << " " << corBranco.s << " " << i << " " << j << endl;
			if(solve(i, j)) ans.pb({i, j});
		}
	}

	if(ans.size() == 0) cout << "None\n";
	else if(ans.size() == 1){
		//cout << ans[0].f << " " << ans[0].s << endl;
		cout << (char)(ans[0].s + 'a' - 1) << n - ans[0].f + 1 << endl;
	}
	else cout << "Multiple\n";
}
