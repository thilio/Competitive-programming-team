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
const int MAXN = 1e5 + 10;

typedef tuple<int, int, int, int> tup;

int n, m;
char mapa[55][55];

bool valid(int x, int y){
	if (x < 0 or y < 0)
		return false;
	if (x >= n or y >= m)
		return false;
	return mapa[x][y] != '#';
}

int mx[4] = {1, -1, 0, 0};
int my[4] = {0, 0, 1, -1};
int memo[55][55][55];
int sx, sy, ex, ey;
int ordx[55], ordy[55], ords;

int dijkstra(){
	memset(&memo, -1, sizeof memo);
	priority_queue< tup, vector<tup>, greater<tup> > fila;

	fila.push({0, sx, sy, 0});

	int x, y, xx, yy, done, dst;
	while (!fila.empty()){
		tie(dst, x, y, done) = fila.top();
		fila.pop();

		if (memo[x][y][done] != -1)
			continue;

		memo[x][y][done] = dst;

		if (done < ords){
			xx = x + ordx[done];
			yy = y + ordy[done];

			if (valid(xx, yy) and memo[xx][yy][done + 1] == -1){
				fila.push({dst, xx, yy, done + 1});
			}
			else if (!valid(xx, yy) and memo[x][y][done + 1] == -1){
				fila.push({dst, x, y, done + 1});
			}
		}

		fr(k, 4){
			xx = x + mx[k];
			yy = y + my[k];
			if (valid(xx, yy) and memo[xx][yy][done] == -1){
				fila.push({dst + 1, xx, yy, done});
			}
		}
	}

	int ans = INF;
	fr(i, ords + 1)
		if (memo[ex][ey][i] != -1)
			ans = min(ans, memo[ex][ey][i]);
	return ans;
}

int32_t main(){
	fastio;
	cin>>n>>m;
	string s;

	fr(i, n){
		cin>>s;
		fr(j, m){
			mapa[i][j] = s[j];
			if (s[j] == 'R')
				sx = i, sy = j;
			if (s[j] == 'E')
				ex = i, ey = j;
		}
	}

	cin>>s;
	ords = s.size();
	fr(i, ords){
		ordx[i] = ordy[i] = 0;
		if (s[i] == 'U')
			ordx[i] = -1;
		else if (s[i] == 'D')
			ordx[i] = 1;
		else if (s[i] == 'R')
			ordy[i] = 1;
		else
			ordy[i] = -1;		
	}

	cout<<dijkstra()<<endl;
}