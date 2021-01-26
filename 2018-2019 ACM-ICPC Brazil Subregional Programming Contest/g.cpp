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
const int maxn = 4000;
const int maxm = 100100;

int p,r,c;
int demand[1500],stocks[1500];
pair<pii,int> edges[20100];
int total;

int ned, first[maxn], work[maxn],q[maxn];
ll dist[maxn];

ll cap[maxm], to[maxm], nxt[maxm];

void init(){
	ms(first,-1);
	ned = 0;

}

void add(int u,int v,int c){
	to[ned] = v;
	cap[ned] = c;
	nxt[ned] = first[u];
	first[u] = ned++;

	to[ned] = u;
	cap[ned] = 0;
	nxt[ned] = first[v];
	first[v] = ned++;

}

ll dfs(int u,ll f,int t){
	if(u == t) return f;
	for(int &e = work[u]; e!= -1; e = nxt[e]){
		int v = to[e];
		if(dist[v] == dist[u] + 1 && cap[e] > 0){
			ll df = dfs(v,min(f,cap[e]),t);
			if(df > 0){
				cap[e] -= df;
				cap[e^1] += df;
				return df;
			}
		}
	}
	return 0;
}

bool bfs(int s,int t){
	ms(dist,-1);
	dist[s] = 0;
	int st,en;
	st = en = 0;
	q[en++] = s;

	while(en > st){
		int u = q[st++];
		for(int e = first[u]; e!= -1; e= nxt[e]){
			int v = to[e];
			if(dist[v] < 0 && cap[e] > 0){
				dist[v] = dist[u] + 1;
				q[en++] = v;
			}
		}
	}

	return dist[t] >= 0;

}

ll dinic(int s,int t){
	ll flow = 0;
	ll f;
	while(bfs(s,t)){
		memcpy(work,first,sizeof work);
		while(f = dfs(s,llINF,t)) flow += f;
	}

	return flow;
}

bool ok(int tempo){

	init();
	int source = 0;
	int sink = p + r + 1;

	frr(i,r){
		add(source,i,stocks[i]);
	}

	frr(i,p){
		add(r + i,sink,demand[i]);
	}

	frr(i,c){
		if(edges[i].snd <= tempo) add(edges[i].fst.fst,r + edges[i].fst.snd,INF);
	}

	if(dinic(source,sink) >= total) return true;
	return false;

}

int main(){

	fastio;

	cin >> p >> r >> c;
	frr(i,p) cin >> demand[i];
	frr(i,p) total += demand[i];

	frr(i,r) cin >> stocks[i];

	frr(i,c){
		cin >> edges[i].fst.snd >> edges[i].fst.fst >> edges[i].snd;
	}

	int l = 0;
	int r = 1e6;

	int best = -1;

	while(l <= r){
		int m = (l + r)/2;

		if(ok(m)){
			best = m;
			r = m -1;
		}
		else l = m + 1;
	}

	cout << best << endl;



}
