/*
   Title: Floyd-Warshall algorithm
   Description: Computes all-pairs shortest path with negative edges
   Complexity:  floyd O(V**3)

   Details: May be used to detect negative cycles. just check the main diagonal for negative edges.
	
	The DP works as follows, dist[i][j][k] = distance between i and j passing through the first k vertices

	One may manipulate this order by using a permutation.
*/

const int INF = 0x3f3f3f3f;
const int MAXN = 200;

int n, m, adj[MAXN][MAXN], dist[MAXN][MAXN];

int floyd(){
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dist[i][j] = adj[i][j];

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (dist[i][k] < INF and dist[k][j] < INF)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

			
	for (int i = 1; i <= n; i++)
		if (dist[i][i] < 0)
			return -1; // negative cycle	

	return 0;	
}
