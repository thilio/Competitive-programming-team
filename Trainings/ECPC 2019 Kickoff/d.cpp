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
int n,m,q;
vi adj[2020];
int dist[2020][2020];
int d[2020];
int dia[1001000];
int cidade[1001000];

void bfs(int v){
	queue<int> q;
	ms(d, -1);
	d[v] = 0;
	q.push(v);
	while(!q.empty()){
		int at = q.front();
		q.pop();
		for(auto x: adj[at]){
			if(d[x] != -1)  continue;
			d[x] = d[at] + 1;
			q.push(x);
		}
	}

	frr(i,n){
		dist[v][i] = d[i];
	}
}

int main(){

	freopen("ysys.in","r",stdin);
	fastio;
	cin >> n >> m >> q;

	fr(i,m){
		int u,v;
		cin >> u >> v;
		adj[v].pb(u);
		adj[u].pb(v);
	}

	frr(i,n) bfs(i);

	fr(i,q){
		cin >> dia[i] >> cidade[i];
	}

	int start = cidade[0];

	int i = 0;
	int day = 0;
	int delta = INF;
	while(i < q){
		delta = min(delta, dia[i] - day);
		if(i == q - 1) break;
		day += dist[cidade[i]][cidade[i + 1]];
		if(dist[cidade[i]][cidade[i+1]] == -1) delta = -2;
		i++;
	}

	ll ans = 0;

	frr(i,n){
		if(dist[start][i] <= delta && dist[start][i] >= 0) ans++;
	}

	cout << ans << endl;




}
