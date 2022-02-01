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

int n;
vi adj[1010];
vi dist[1010];
int d[1010];
int vis[1010];

void bfs(int v){
	queue<int> q;
	q.push(v);
	d[v] = 0;

	vis[v] = 1;

	while(!q.empty()){
		int u = q.front();
		q.pop();

		for(auto x : adj[u]){
			if(vis[x]) continue;
			vis[x] = 1;
			d[x] = d[u] + 1;
			q.push(x);
		}

	}
}
int main(){

	fastio;
	cin >> n;
	string s;

	getline(cin,s);

	fr(i,n){
		getline(cin,s);
		for(int j = i + 1; j < n; j++){
			if(s[j] == '1') adj[i].pb(j);
			else adj[j].pb(i);
		}
	}

	bfs(0);

	fr(i,n){
		if(!vis[i]){
			cout << "impossible\n";
			return 0;
		}
	}

	fr(i,n){
		dist[d[i]].pb(i);
	}

	for(int i=n; i >0 ; i--){
		fr(j,dist[i].size()){
			cout << dist[i][j] << ' ';
		}
	}

	cout << 0 << endl;



}
