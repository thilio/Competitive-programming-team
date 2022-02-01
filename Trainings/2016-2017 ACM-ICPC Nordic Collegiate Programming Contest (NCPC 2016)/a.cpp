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

int n, m, q;
int mat[1010][1010];
int vis[1010][1010];
int id[1000100], sz[1000100];
pii ini[100100], fim[100100];
int c;

vi ans;

int dx[4] = {1, -1, 0 ,0};
int dy[4] = {0, 0, 1, -1};


int casa(int i, int j){
	return (i - 1)*m + j;
}

bool is(int i, int j){
	if(i < 1 || i > n || j < 1 || j > m) return false;
	return true;
}

int find(int i){
	if(id[i] == i) return i;
	return id[i] = find(id[i]);
}

bool merge(int u, int v){
	u = find(u);
	v = find(v);
	if(u == v) return false;
	if(sz[u] > sz[v]) swap(u, v);
	id[u] = v;
	sz[v] += sz[u];
	return true;
}

void dfs(int  i, int j){
	vis[i][j] = 1;

	fr(k, 4){
		if(is(i + dy[k], j + dx[k]) && vis[i + dy[k]][j + dx[k]] == 0 && mat[i + dy[k]][j + dx[k]] == 0){
			merge(casa(i, j), casa(i + dy[k],j + dx[k]));
			dfs(i + dy[k], j + dx[k]);
		}
	}
}



void init(){
	frr(i, n*m){
		id[i] = i;
		sz[i] = 1; 
	}
}

void desfaz(int i, int j){
	mat[i][j]--;
	if(mat[i][j] > 0) return;

	c++;

	fr(k, 4){
		int il = i + dy[k];
		int jl = j + dx[k];
		if(is(il, jl) && mat[il][jl] == 0) 
			if(merge(casa(i, j), casa(il, jl))) c--;
	}
}

int main(){

	fastio;

	cin >> m >> n >> q;

	frr(i, q){
		int xs,ys,xf,yf;
		cin >> xs >> ys >> xf >> yf;
		ini[i] = mp(xs, ys);
		fim[i] = mp(xf, yf);  
		if(xs == xf){
			for(int j = ys; j <= yf; j++) mat[j][xs]++;
		}
		else{
			for(int j = xs; j <= xf; j++) mat[ys][j]++;
		}
	}


	init();
	c = 0;

	frr(i, n){
		frr(j, m){
			if(vis[i][j] == 0 && mat[i][j] == 0){
				dfs(i, j);
				c++;
			}	
		}	
	}


	ans.pb(c);
	for(int i = q; i > 0; i--){
		int xs,ys,xf,yf;
		xs = ini[i].fst;
		ys = ini[i].snd;
		xf = fim[i].fst;
		yf = fim[i].snd;  
		if(xs == xf){
			for(int j = ys; j <= yf; j++) desfaz(j, xs);
		}
		else{
			for(int j = xs; j <= xf; j++) desfaz(ys, j);
		}
		ans.pb(c);
	}

	reverse(all(ans));

	frr(i, q) cout << ans[i] << endl;




}
