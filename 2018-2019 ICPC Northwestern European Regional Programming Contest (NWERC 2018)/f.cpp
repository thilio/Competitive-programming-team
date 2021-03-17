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
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 3e3 + 10;

int n, pai[MAXN], cost[MAXN][MAXN];
ll ans;

int root[MAXN], vis[MAXN], cicle[MAXN];

int dfs(int v){
	if (vis[v]) // raiz visitada novamente
		root[v] = v;
	else if (root[pai[v]] != -1) // arvore
		root[v] = root[pai[v]];
	else{
		vis[v] = 1;
		root[v] = dfs(pai[v]);
		cicle[v] = vis[root[v]]; // esta em ciclo
		vis[v] = 0;
	}

	return root[v];
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n;

	n++;

	frr(i, n - 1){
		int s;
		cin>>pai[i]>>s;
		ans += s;
		fr(j, n){
			cin>>cost[j][i];
			cost[j][i] -= s;
		}
	}

	memset(root, -1, sizeof root);
	for (int i = n; i > 0; i--)
		if (root[i] == -1)
			dfs(i);

	for (int i = 1; i < n; i++){
		if (root[i] == i){
			int mnv = i;
			for (int j = 1; j < n; j++)
				if (root[j] == i and cicle[j] and cost[n - 1][j] <= cost[n - 1][mnv])
					mnv = j;

			int aux = cost[n - 1][mnv];
			ans += aux;
			for (int j = 0; j < n; j++)
				if (root[j] == i and cicle[j])
					for (int k = 0; k <= n; k++)
						cost[k][j] -= aux;
		}			
	}

	for (int i = 0; i < n; i++)
		for (int j = 1; j < n; j++)
			if (i == pai[j] or (root[i] == root[j] and cicle[i]))
				cost[i][j] = 0;

	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;				
	pq.push({0, 0});

	ll dst, vtx;
	while (!pq.empty()){ // dijkstra para achar melhor caminhoa te n - 1
		tie(dst, vtx) = pq.top();
		pq.pop();

		if (!vis[vtx]){
			vis[vtx] = 1;
			for (int j = 0; j < n; j++)
				if (!vis[j])
					pq.push({dst + cost[vtx][j], j});
			cost[0][vtx] = dst;
		}
	}

	ans += cost[0][n - 1];

	cout<<ans<<endl;
}