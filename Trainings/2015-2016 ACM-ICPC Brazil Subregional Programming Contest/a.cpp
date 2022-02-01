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
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 2e5 + 10;

int n, m;
int dist[MAXN];

vii adj[MAXN];

void dij(int src){
	memset(dist, -1, sizeof dist);
	priority_queue<pii, vector<pii>, greater<pii> > pq;

	pq.push({0, src});

	int dst, vtx;

	while (!pq.empty()){
		tie(dst, vtx) = pq.top();
		pq.pop();

		if (dist[vtx] != -1)
			continue;

		dist[vtx] = dst;
	
		for (auto x : adj[vtx])
			if (dist[x.fst] == -1)
				pq.push({dst + x.snd, x.fst});
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>n>>m;

	int x, y, w;
	fr(i, m){
		cin>>x>>y>>w;
		x--; y--;

		adj[x<<1].pb({y<<1|1, w});
		adj[y<<1|1].pb({x<<1, w});

		adj[y<<1].pb({x<<1|1, w});
		adj[x<<1|1].pb({y<<1, w});
	}

	dij(0);

	cout<<dist[(n - 1)<<1]<<endl;
}