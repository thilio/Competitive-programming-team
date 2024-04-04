/* Computes the maximum matching in a bipartite graph
hopcroftKarp O(E(V**1/2))
Min_cover O(V)
Vetices numberd from 1 to m in U and from 1 to n in V.

- Min cover is the complement of max stable set
- No isolated vertices => Edge-cover(G) + match(G) = V
- In DAG : |Largest antichain| = |Smallest path cover|*/
vector<int> adju[MAXN]; // Anjacency of U (size m)
int matchu[MAXN], matchv[MAXN], coveru[MAXN], coverv[MAXN]; 
int m, n, dist[MAXN], q[MAXN];
void min_cover(){
	for (int u = 1; u <= m; u++)
		coveru[u] = (dist[u] == INF? true:false);
	for (int v = 1; v <= n; v++)
		coverv[v] = (dist[matchv[v]] != INF? true:false);	
}
bool bfs(){
	int st = 0, en = 0;
	for (int u = 1; u <= m; u++){
		if (matchu[u] == 0)
			dist[u] = 0, q[en++] = u;
		else dist[u] = INF;
	}
	dist[0] = INF;
	while (en > st){
		int u = q[st++];
		if (dist[u] >= dist[0]) continue;
		for (int v : adju[u])
			if (dist[matchv[v]] == INF){
				dist[matchv[v]] = dist[u] + 1;
				q[en++] = matchv[v];
			}
	}
	return (dist[0] != INF);
}
bool dfs(int u){
	if (u == 0) return true;
	for (int v : adju[u]){
		if (dist[matchv[v]] == dist[u] + 1){
			if (dfs(matchv[v])){
				matchv[v] = u; matchu[u] = v;
				return true;
			}
		}
	}
	dist[u] = INF;
	return false;
}
int HopcroftKarp(){
	memset(&matchu, 0, sizeof matchu);
	memset(&matchv, 0, sizeof matchv);
	int result = 0;
	while (bfs())
		for (int u = 1; u <= m; u++)
			if (matchu[u] == 0 and dfs(u)) result++;
	min_cover();
	return result;
}