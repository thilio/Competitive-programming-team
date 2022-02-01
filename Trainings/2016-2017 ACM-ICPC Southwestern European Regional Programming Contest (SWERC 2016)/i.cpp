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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 200 + 10;
const int mod = 13;

int n, m;

int invmod[mod];
int fastxp(int base, int exp){
	int ans = 1;
	while (exp){
		if (exp & 1)
			ans = (ans * base) % mod;
		base = (base * base) % mod;
		exp >>= 1;
	}
	return ans;
}


int edge[MAXN][MAXN], ed = 1;
int mat[500][202], val[202];

void gauss(){
	vi where(201, -1);
	for (int col = 1, row = 0; col < 201 and row < m; col++){
		int sel = row;
		for (int i = row; i < m; i++)
			if (mat[i][col] > mat[sel][col])
				sel = i;
		
		if (mat[sel][col] == 0)
			continue;

		for (int i = col; i <= 201; i++)
			swap(mat[sel][i], mat[row][i]);

		where[col] = row;

		for (int i = 0; i < m; i++)
			if (i != row){
				int c = (mat[i][col] * invmod[mat[row][col] % mod]) % mod;
				for (int j = col; j <= 201; j++){
					int aux = (mat[row][j] * c) % mod;
					mat[i][j] = (mat[i][j] - aux + mod) % mod;
				}
			}
		row++;	
	}

	for (int i = 1; i < 201; i++)
		if (where[i] != -1)
			val[i] = (mat[where[i]][201] * invmod[mat[where[i]][i] % mod]) % mod;
}

vii adj[220];

int dist[220];

int dijkstra(int src, int snk){
	memset(dist, -1, sizeof dist);	
	priority_queue<pii, vii, greater<pii>> pq;

	pq.push({0, src});

	int dst, v;
	
	while (!pq.empty()){
		tie(dst, v) = pq.top();
		pq.pop();

		if (dist[v] != -1)
			continue;

		dist[v] = dst;
		for (auto x : adj[v])
			if (dist[x.fst] == -1)
				pq.push({dst + x.snd, x.fst});
	}


	return dist[snk];
}	


signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	fr(i, mod)
		invmod[i] = fastxp(i, mod - 2);

	int a, r;	
	cin>>n>>a>>r>>m;

	int d, p, lst;
	fr(i, m){
		cin>>d>>p;
		lst = -1;

		mat[i][201] = d;

		int x;
		while (p--){
			cin>>x;
			if (lst != -1){
				if (edge[lst][x] == 0)
					edge[lst][x] = edge[x][lst] = ed++;
				mat[i][edge[lst][x]]++;
			}

			lst = x;
		}
	}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < 202; j++)
			mat[i][j] %= mod;	

	gauss();	

	frr(i, n)
		frr(j, n)
			if (edge[i][j])
				adj[i].pb({j, val[edge[i][j]]});

	cout<<dijkstra(a, r)<<endl;		
}