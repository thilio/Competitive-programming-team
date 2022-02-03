/*
   Title: Hopcroft-Karp algorithm for maximum matching
   Description: Computes the maximum matching in a bipartite graph
   Complexity:  hopcroftKarp O(E(V**1/2))
   		Min_cover O(V)

   Details: Only the adjacency of one side is needed.
	Vetices numberd from 1 to m in U and from 1 to n in V.

	Konig-Egervary's theo: In bip. graphs match(G) = cover(G);
	Gallai ID1: Min cover is the complement of max stable set;
	Gallai ID2: If not isolated vertices, Edge-cover(G) + match(G) = V.
	Dilwoth's L: In a partial order |Largest antichain| = |Sammalest path cover| 

   Credits: https://github.com/splucs/Competitive-Programming/tree/master/Macac%C3%A1rio
*/

using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 10;

vector<int> adju[MAXN]; // Anjacency of U (size m)
int matchu[MAXN], matchv[MAXN], coveru[MAXN], coverv[MAXN]; 
int dist[MAXN], q[MAXN];
int m, n;

void min_cover(){ // If not needed, do not copy
	for (int u = 1; u <= m; u++){
		coveru[u] = false;
		if (dist[u] == INF)
			coveru[u] = true;	
	}	
	for (int v = 1; v <= n; v++){
		coverv[v] = false;
		if (dist[matchv[v]] != INF)
			coverv[v] = true;
	}	
}

bool bfs(){
	int st = 0, en = 0;
	for (int u = 1; u <= m; u++){
		if (matchu[u] == 0){
			dist[u] = 0; 
			q[en++] = u;
		}
		else dist[u] = INF;
	}
	dist[0] = INF;
	while (en > st){
		int u = q[st++];
		if (dist[u] >= dist[0]) 
			continue;
		for (int v : adju[u]){
			if (dist[matchv[v]] == INF){
				dist[matchv[v]] = dist[u] + 1;
				q[en++] = matchv[v];
			}
		}
	}

	return (dist[0] != INF);
}

bool dfs(int u){
	if (u == 0) return true;
	for (int v : adju[u]){
		if (dist[matchv[v]] == dist[u] + 1){
			if (dfs(matchv[v])){
				matchv[v] = u; 
				matchu[u] = v;
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
	while (bfs()){
		for (int u = 1; u <= m; u++){
			if (matchu[u] == 0 and dfs(u))
				result++;
		}
	}
	min_cover();
	return result;
}
