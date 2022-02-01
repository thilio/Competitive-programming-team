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

int n,m,k;
ll esp[500500];
ll dist[500500];
ll peso[500500];
ll vis[500500];
ll dono[500500];

vector<pll> adj[300300];

void dijsktra(){

	priority_queue<pll, vector<pll>, greater<pll>> pq;

	frr(i,n) dist[i] = llINF;
	fr(i,k){
		dist[esp[i]] = 0;
		pq.push({0,esp[i]});
		dono[esp[i]] = esp[i];
	}

	while(!pq.empty()){
		ll dst, vtx;
		tie(dst, vtx) = pq.top();
		pq.pop();

		if(vis[vtx]) continue;
		vis[vtx] = 1;

		for(auto x: adj[vtx]){
			if(dist[x.fst] > dst + x.snd){
				dist[x.fst] = dst + x.snd;
				dono[x.fst] = dono[vtx];
				pq.push({dist[x.fst], x.fst});
			}
			if(dist[x.fst] == dst + x.snd && dono[x.fst] > dono[vtx]){
				dono[x.fst] = dono[vtx];
				pq.push({dist[x.fst], x.fst});
			}
		}



	}
}

int main(){

	fastio;

	cin >> n >> m;

	fr(i,m){
		ll a,b,w;
		cin >> a >> b >> w;
		adj[a].pb(mp(b,w));
		adj[b].pb(mp(a,w));
	}

	cin >> k;

	fr(i,k) cin >> esp[i];

	dijsktra();

	frr(v,n){
		for(auto x : adj[v]){
			ll c,u;
			tie(u,c) = x;
			if(dono[v] == dono[u]){
				peso[dono[v]] += 2*c;
			}
			else{
				peso[dono[v]] += dist[u] - dist[v] + c;
				peso[dono[u]] += dist[v] - dist[u] + c;
			}
		}

		//dbg(peso[1]);
	}

	fr(i,k){
		peso[esp[i]] /= 2;
		cout << peso[esp[i]]/2;
		if(peso[esp[i]]%2 == 1) cout << ".5" << endl;
		else cout << ".0" << endl;
	}


}
