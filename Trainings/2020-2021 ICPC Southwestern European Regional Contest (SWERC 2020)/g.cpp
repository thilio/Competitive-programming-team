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
const int MAXN = 1000001;

ll cost[MAXN][20];
int nxt[MAXN][20];

int vis[MAXN];
int cycle[MAXN];
int sz[MAXN];
int dist[MAXN];
int dv[MAXN];

int cy = 1;

int n, K;
void pre(){
	for(int i = 1; i <= n; i++){
		for(int j = i; j <= n; j+= i) dv[j]++;
	}
}

void build(){
	pre();

	for(int i = 0; i < n; i++){
		nxt[i][0] = (i + dv[i])%n;
		cost[i][0] = i;
	}
	for(int k = 1; k < 20; k++){
		for(int i = 0; i < n; i++){
			nxt[i][k] = nxt[nxt[i][k - 1]][k - 1];
			cost[i][k] = cost[i][k - 1] + cost[nxt[i][k - 1]][k - 1]; 
		}
	}
}

void dfs(int i){
	vis[i] = 1;

	if(vis[nxt[i][0]] == 0){
		dfs(nxt[i][0]);
	}
	else if(vis[nxt[i][0]] == 1){
		cycle[i] = cy++;
	}
	vis[i] = 2;
}

void propagate(){
	fr(i, n){
		if(cycle[i] != 0 && sz[cycle[i]] == 0){
			int v = nxt[i][0];
			int tam = 1;
			while(v != i){
				cycle[v] = cycle[i];
				tam++;
				v = nxt[v][0];
			}
			sz[cycle[i]] = tam;
		}
	}
}

void calc_d(int i){
	if(dist[i] != -1) return;
	if(cycle[i] != 0){
		dist[i] = 0;
		return;
	}
	calc_d(nxt[i][0]);
	dist[i] = dist[nxt[i][0]] + 1;
}

ll tent(int i){
	int cyy = cycle[nxt[nxt[i][19]][19]];
	int aux = sz[cyy];

	if(aux + dist[i] < K) return llINF;

	int tam = K;
	ll resp = 0;
	for(int k = 19; k >= 0; k--){
		if((1ll << k) <= tam){
			resp += cost[i][k];
			i = nxt[i][k];
			tam -= (1ll << k);
		}
	} 
	return resp;
}

void print(int i){
	if(i == -1) cout << -1 << endl;
	else{
		int j = 1;
		while(j <= K){
			cout << i << ' ';
			i = nxt[i][0];
			j++;
		}
		gnl;
	}
}

int main(){

	fastio;
	cin >> n >> K;
	build();
	
	fr(i, n){
		if(vis[i] == 0) dfs(i);
	}
	//olar;
	propagate();
	//olar;
	ms(dist, -1);
	fr(i, n){
		calc_d(i);
	}
	//fr(i, n) dbg(sz[i]);
	ll ans = llINF;
	int save = -1;
	fr(i, n){
		if(ans > tent(i)){
			ans = tent(i);
			save = i;
		}
	}

	print(save);
}
