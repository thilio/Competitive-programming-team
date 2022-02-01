// Algoritmo de Tarjan para componente biconexa
// complexidade : O(V + E)
// cuidado, as ligações entre componentes são vertices

#include "bits/stdc++.h"
using namespace std;

const int MAXN = 1e5 + 10;

int n, m, clk, id;
int pre[MAXN], lo[MAXN], bcc[MAXN]; // bcc[v] é a componente biconexa de v
stack< pair<int, int> > stk;
vector<int> adj[MAXN];

int ans;

void markcomp(int v, int u){
	if (v > u) swap(u, v);
	int a, b, sz = 0;
	id++;
	do { // cuidado, vertices de ligação podem mudar de componente
		tie(a, b) = stk.top();
		stk.pop();
		if (bcc[a] < id)
			bcc[a] = id, sz++;
		if (bcc[b] < id)
			bcc[b] = id, sz++;
	} while (a != v or b != u);

	ans = max(ans, sz); // tamanho da maior componente biconexa
}	

void dfsbcc(int v, int p){
	lo[v] = pre[v] = clk++;
	for (auto x : adj[v]){
		if (pre[x] == -1){ 
			stk.push({min(v, x), max(v, x)});
			dfsbcc(x, v); 
			
			if (lo[x] >= pre[v]) // achei compoente
				markcomp(v, x);
			lo[v] = min(lo[v], lo[x]);
		} 
		else if (x != p and pre[x] < pre[v]){
			stk.push({min(v, x), max(v, x)});
			lo[v] = min(lo[v], pre[x]);
		} 
	} 
}

int findbcc(){
	fill(pre, pre + n + 1, -1);
	fill(bcc, bcc + n + 1, -1);
	clk = id = 0;
	for (int v = 1; v <= n; v++) // indexado de um
		if (pre[v] == -1)
			dfsbcc(v, v);
		
	return id;
}

int main(){
	cin>>n>>m;

	int a, b;
	for (int i = 0; i < m; i++){
		cin>>a>>b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	findbcc();

	cout<<ans<<endl;
}
