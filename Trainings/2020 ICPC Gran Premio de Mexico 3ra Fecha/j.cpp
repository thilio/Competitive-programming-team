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

ll dist[1010][1010];
ll memo[10100][1010][2];
vi adj[1010];
ll dest[1010];
ll val[1010];
ll ped[1010];
int n, m;
int o, t;
ll k;

void bfs(int v){
	dist[v][v] = 0;
	queue<int> q;
	q.push(v);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(auto x: adj[u]){
			if(dist[v][x] == -1){
				dist[v][x] = dist[v][u] + k;
				q.push(x);
			}
		}
	}
}

ll dp(int temp, int i, int last){
	if(temp < 0) return -llINF;
	int v = (last ? dest[i - 1] : ped[i - 1]);
	if(i > o){
		if(temp >= dist[v][1]) return 0;
		else return -llINF;
	}

	ll &pdm = memo[temp][i][last];
	if(pdm != -1) return pdm;

	pdm = dp(temp - dist[v][ped[i]], i + 1, 0);
	pdm = max(pdm, val[i] + dp(temp - dist[v][ped[i]] - dist[ped[i]][dest[i]], i + 1, 1));

	return pdm;
}

int main(){

	fastio;

	cin >> n >> m >> k;
	ms(dist , -1);

	fr(i, m){
		int a, b;
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	frr(i, n) bfs(i);

	ms(memo, -1);

	cin >> o >> t;

	frr(i, n) frr(j, n) if(dist[i][j] == -1) dist[i][j] = t + 1;

	frr(i, o) cin >> ped[i];

	frr(i, o) cin >> dest[i] >> val[i];

	ped[0] = dest[0] = 1;

	ll x = dp(t, 1, 1);

	if(x < 0){
		cout << "Impossible" << endl;
	}
	else{
		cout << x << endl;
	}




}
