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
const int MAXN = 5e4 + 10;
const int LMAXN = 18;

int n, hgt[MAXN], memo[MAXN][LMAXN]; 
bool vis[MAXN]; 
vi adj[MAXN]; 

void dfs_lca(int v){
	vis[v] = 1; 
	for (auto x : adj[v]){
		if (vis[x]) 
			continue;
		hgt[x] = hgt[v] + 1; 
		memo[x][0] = v; 
		for (int i = 1; i < LMAXN; i++) 
			memo[x][i] = memo[memo[x][i-1]][i-1];
		dfs_lca(x);
	}
}

void build_lca(){
	for (int i = 0; i < LMAXN; i++) 
		memo[1][i]=1;
	hgt[1] = 0;
	dfs_lca(1); 
}

int find_lca(int a, int b){
	if (hgt[a] < hgt[b])
		swap(a, b); 
	for (int i = LMAXN - 1; i >= 0; i--) // equilibra os vértices
		if (hgt[memo[a][i]] >= hgt[b])
			a = memo[a][i];
	if (a == b) 
		return a; 
	for (int i = LMAXN - 1; i >= 0; i--) // sobe junto
		if (memo[a][i] != memo[b][i]){
			a = memo[a][i];
			b = memo[b][i];
		}
	return memo[a][0]; // para imediatamente antes do lca
}

int k, freq[MAXN], lcat[15][15];
ll cost[15];
vi node;
void calc_cost(){
	cost[0] = 0;
	for (int i = 1; i <= k; i++){
		ll best = 1e5;
		for (int j = 0; j < i; j++)
			best = min(best, cost[i - j] + cost[j]);
		cost[i] = best;
	}
}

typedef tuple<int, int, int> tup;

priority_queue<tup> lca;

ll solve(){
	ll cst = 0;
	int d, a, b;
	
	while (!lca.empty()){
		tie(d, a, b) = lca.top();
		lca.pop();
		if (freq[node[a]] == 0 or freq[node[b]] == 0 or node[a] == node[b])
			continue;
	
		if (a > b)
			swap(a, b);

		// cout<<"--: "<<d<<' '<<node[a]<<' '<<node[b]<<endl;
		// dbg(((ll) hgt[node[a]] - d) * cost[freq[node[a]]]);
		// dbg(((ll) hgt[node[b]] - d) * cost[freq[node[b]]]);

		cst += ((ll) hgt[node[a]] - d) * cost[freq[node[a]]];
		cst += ((ll) hgt[node[b]] - d) * cost[freq[node[b]]];

		if (node[b] == find_lca(node[a], node[b])){
			freq[node[b]] += freq[node[a]];
			freq[node[a]] = 0;
			node[a] = node[b];
		}
		else if (node[a] == find_lca(node[a], node[b])){
			freq[node[a]] += freq[node[b]];
			freq[node[b]] = 0;
		}
		else{
			freq[find_lca(node[a], node[b])] += freq[node[a]] + freq[node[b]];
			freq[node[a]] = freq[node[b]] = 0;
			node[a] = find_lca(node[a], node[b]);
		}
		
		// if (freq[node[a]] == k){
		// 	break;
		// }

//		dbg(freq[node[a]]);
		for (int i = 0; i < k; i++)
			if (node[i] != node[a] and node[i] != node[b] and freq[node[i]] != 0)
				lca.push({hgt[find_lca(node[a], node[i])], a, i});
	}
	for (auto i : node){
		cst += hgt[i] * cost[freq[i]];
		freq[i] = 0;
	}

	return cst;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n;

	int a, b;
	fr(i, n - 1){
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	build_lca();

	int q;
	cin>>q;
	while (q--){
		cin>>k;

		fr(i, k){
			cin>>a;
			freq[a]++;
			node.pb(a);
		}
	
		frr(i, k)
			cin>>cost[i];
		calc_cost();
		
		// k++;
		// cost[k] = 0;
		// node.pb(1);
		// freq[1]++;

		sort(all(node));
		k = (int) (unique(all(node)) - node.begin());
		if (node[0] == 1){
			node.erase(node.begin());
			k--;
		}
		freq[1] = 0;

		while (node.size() > k)
			node.pop_back();

		// dbg(k);
		// for (auto x : node)
		// 	dbg(x);

		for (int i = 0; i < k; i++)
			for (int j = 0; j < i; j++){
				lca.push({hgt[find_lca(node[i], node[j])], i, j});
//				cout<<"lca :" << find_lca(node[i], node[j])<< ' '<<node[i]<<' '<<node[j]<<endl;
			}
	
		cout<<solve()<<endl;

		freq[1] = 0;
		node.clear();
	}


}