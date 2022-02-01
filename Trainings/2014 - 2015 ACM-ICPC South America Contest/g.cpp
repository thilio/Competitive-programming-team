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

vi adj[100100];
map<pll, int> star;
vector<pll> v;
int vis[100100];
int tem[100100];
int n;

ll dist(int i, int j){
	return (v[i].fst - v[j].fst)*(v[i].fst - v[j].fst) + (v[i].snd - v[j].snd)*(v[i].snd - v[j].snd);
}

void dfs(int v, int cor){
	vis[v] = cor;
	for(auto x: adj[v]){
		if(vis[x] == 0) dfs(x, cor^1);
	} 
}


int main(){

	fastio;

	cin >> n;
	v.pb({-1, - 1});

	frr(i, n){
		int x, y;
		cin >> x >> y;
		v.pb({x, y});
		star[{x, y}] = i;
	}


	frr(i, n){
		for(int x = v[i].fst - 5; x <= v[i].fst + 5; x++){
			//dbg(x);	
			for(int y = v[i].snd - 5; y <= v[i].snd + 5; y++){
				if(!star.count({x, y}))continue;
				int k = star[{x, y}];

				if(x == v[i].fst && y == v[i].snd) continue;
				if(k != 0){
					if(dist(i,k) <= 25){
						adj[i].pb(k);
					}
				}
			}
		}
	}

	int c = 2;

	frr(i, n){
		if(!vis[i]){
			dfs(i, c);
			c+= 2;
		}
	}
	c -= 2;

	//frr(i, n) dbg(vis[i]);
	frr(i, n) tem[vis[i]]++;
	//frr(i, c) dbg(tem[i]);
	int ans = 0;
	for(int i = 2; i <= c; i+= 2){
		ans += min(tem[i], tem[i^1]);
	}

	cout << ans << endl;

}
