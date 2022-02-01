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

vector<pair<ll, pll>> adj[1010];
long double dist[1010];

long double dijkstra(long double t){
	frr(i, n) dist[i] = -1;

	priority_queue<pair<long double, int>, vector<pair<long double, int>>, greater<pair<long double, int>>> pq;

	pq.push(mp(0, 1));

	while(!pq.empty()){
		long double d;
		int u;
		tie(d, u) = pq.top();
		pq.pop();
		if(dist[u] >= 0) continue;
		dist[u] = d;

		for(auto x: adj[u]){
			int v = x.fst;
			if(dist[v] < -0.5){
				long double c = x.snd.fst*t + x.snd.snd;
				pq.push(mp(dist[u] + c, v));
			}
		}
	}

	return dist[n];
}

int main(){

	fastio;
	cout << setprecision(5) << fixed;

	cin >> n >> m;

	frr(i, m){
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		pll x = {a, b};
		adj[u].pb(mp(v, x));
		adj[v].pb(mp(u, x));
	}

	long double l = 0;
	long double r = 24*60;

	frr(i, 80){
		long double m1 = l + (r - l)/3;
		long double m2 = r - (r - l)/3;

		long double a1 = dijkstra(m1);
		long double a2 = dijkstra(m2);

		if(a1 <= a2) l = m1;
		else r = m2;
	}

	///dbg(l);

	cout << dijkstra(l) << endl;

}
