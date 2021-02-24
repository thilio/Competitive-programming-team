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
vii adj[100100];
bool freq[100100]; // Can find distinct shortest path
int d[100100];
int vis[100100];

void dijkstra(){
	frr(i,n) d[i] = MOD;
	priority_queue<pii, vector<pii>, greater<pii> > pq;
	d[1] = 0;
	pq.push({d[1],1});

	while(!pq.empty()){
		pii at = pq.top();
		pq.pop();

		if(vis[at.snd]) continue;
		vis[at.snd] = 1;

		for(auto &x: adj[at.snd]){
			if(d[x.fst] > at.fst + x.snd){
				d[x.fst] = at.fst + x.snd;
				freq[x.fst] = freq[at.snd];
				pq.push(mp(d[x.fst],x.fst));
			}
			else if(d[x.fst] == at.fst + x.snd){
				freq[x.fst] = true;
			}
		}
	}
}

int main(){

	fastio;

	cin >> n >> m >> k;
	frr(i,k){
		int x;
		cin >> x;
	}
	frr(i,m){
		int a,b,c;
		cin >> a >> b >> c;
		adj[a].pb({b,c});
		adj[b].pb({a,c});
	}

	dijkstra();

	if(freq[n]) cout << "yes" << endl;
	else cout << "no" << endl;

}
