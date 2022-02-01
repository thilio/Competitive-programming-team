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

int n, m, k;
int minr[MAXN], deg[MAXN], color[MAXN], maxr[MAXN], vis[MAXN];
vi adj[MAXN], order[MAXN];
bool ok;

void dfs(int v){
	int mn = 1;
	vis[v] = 1;
	for (int x : adj[v]){
		if (!vis[x])
			dfs(x);
		mn = max(mn, minr[x] + 1); // calcula menor rank possível
	}

	if (minr[v] != 0){
		if (mn > minr[v])
			ok = 0; // deu errado
	}
	else
		minr[v] = mn; // calculei menor rank possível;
	
	if (mn > k) // deu errado
		ok = 0;
}



int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n>>m>>k;

	frr(i, n){
		cin>>color[i];
		minr[i] = color[i];
	}	

	int x, y;
	fr(i, m){
		cin>>x>>y;
		deg[y]++;
		adj[x].pb(y);
	}

	/// cicle detection
	memset(maxr, INF, sizeof maxr);	
	frr(i, n)
		if (minr[i] > 0)
			maxr[i] = minr[i];

	queue<int> fila;
	frr(i, n)
		if (deg[i] == 0){
			fila.push(i);

			maxr[i] = min(maxr[i], k);
			order[maxr[i]].pb(i);
		}


	int cnt = 0, vtx;
	while (!fila.empty()){
		vtx = fila.front();
		fila.pop();
		cnt++;
		for (int x : adj[vtx]){
			deg[x]--;
			maxr[x] = min(maxr[x], maxr[vtx] - 1);
			if (deg[x] == 0){
				fila.push(x);

				if (maxr[x] <= 0){
					cout<<-1<<endl;
					return 0;
				}	

				order[maxr[x]].pb(x); // order[i] são os vertices com upper bound i
			}
		}
	}	

	if (cnt != n){ // cicle
		cout<<-1<<endl;
		return 0;
	}	

	ok = 1;

	for (int i = 1; i <= n; i++)
		if (!vis[i])
			dfs(i);

	if (!ok){
		cout<<-1<<endl;
		return 0;
	}

	priority_queue<pii> pq;	

	for (int rnk = k; rnk > 0; rnk--){
		for (auto x : order[rnk]) // vertices com upper bound rnk
			pq.push({minr[x], x});// tenho que colorir até o lower bound chegar
	
		if (pq.empty()){ // ninguem tem cor rnk
			cout<<-1<<endl;
			return 0;
		}

		do{
			color[pq.top().snd] = rnk;
			pq.pop();
		} while (!pq.empty() and pq.top().fst == rnk); // só coloco se sou obrigado
	}


	frr(i, n)
		cout<<color[i]<<' ';
	gnl;			
}