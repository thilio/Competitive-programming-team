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
int n, m;
vi adj[100100];
int dist[100100];

void bfs(){
	ms(dist, -1);
	queue<int> q;
	q.push(1);
	dist[1] = 0;

	while(!q.empty()){
		int v = q.front();
		q.pop();
		for(auto x: adj[v]){
			if(dist[x] == -1){
				dist[x] = dist[v] + 1;
				q.push(x);
			}
		}
	}
}

int f(int mx){
	int ct = 0;
	bool flag = false;
	while(mx != 1){
		if(mx&1) flag = true;
		ct++;
		mx /= 2;
	}

	return ct + flag;
}

void finish(){
	cout << -1 << endl;
	exit(0);
}

int main(){

	fastio;

	cin >> n >> m;

	fr(i, m){
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	bfs();	
	int mx = -1;
	frr(i, n){
		mx = max(mx, dist[i]);
		if(dist[i] == -1) finish();
	}



	cout << f(2*mx) << endl;
}
