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
ll B;
int n;

map<string, int> m;
vector<pair<int,pll>> adj[100100];
vi topo;

ll cost[100100];
ll prest[100100];

int in[100100];
int tot;

ll memo[10010][2];

void dp(){

	for(int i = tot; i >= 1; i--){
		for(ll cap = 0; cap <= B; cap++){
			memo[cap][0] = memo[cap][1];
			if(cap >= cost[i]){
				memo[cap][0] = max(memo[cap][0], memo[cap - cost[i]][1] + prest[i]);
			}
		}
		for(int cap = 0; cap <= B; cap++){
			memo[cap][1] = memo[cap][0];
		}
	}
}

void toposort(){
	queue<int> q;
	frr(i,tot){
		if(in[i] == 0){
			q.push(i);
			topo.pb(i);
			cost[i] = 0;
		}
	}

	while(!q.empty()){
		int at = q.front();
		q.pop();
		for(auto x: adj[at]){
			in[x.fst]--;
			if(in[x.fst] == 0){
				topo.pb(x.fst);
				q.push(x.fst);
			}
		}
	}

}

int main(){

	fastio;

	cin >> B;
	cin >> n;

	int ct = 1;
	fill(cost, cost + 100100, llINF);

	fr(i,n){
		string s,t;
		int u,v;
		cin >> s >> t;
		if(m.count(s) == 0){
			m[s] = ct++;
			u = ct - 1;
		}
		else{
			u = m[s];
		}
		if(m.count(t) == 0){
			m[t] = ct++;
			v = ct - 1;
		}
		else{
			v = m[t];
		}
		cin >> s;

		int c,p;
		cin >> c >> p; 
		adj[v].pb({u,{c,p}});
		in[u]++;
	}

	tot = ct - 1;
	toposort();

	fr(i, tot){
		int u = topo[i];
		for(auto x : adj[u]){
			int v = x.fst;
			pii aux = x.snd;

			if(cost[v] > cost[u] + aux.fst){
				cost[v] = cost[u] + aux.fst;
				prest[v] = prest[u] + aux.snd;
			}

			if(cost[v] == cost[u] + aux.fst && prest[v] < prest[u] + aux.snd){
				cost[v] = cost[u] + aux.fst;
				prest[v] = prest[u] + aux.snd;	
			}
		}
	}

	dp();

	cout << memo[B][0] << endl;

	fr(i, B + 1){
		if(memo[i][0] == memo[B][0]){
			cout << i << endl;
			return 0;
		}
	}

}
