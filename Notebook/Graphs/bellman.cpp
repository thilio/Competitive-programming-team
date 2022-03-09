/*
   Title: Bellman-Ford algorithm
   Description: Computes single source shortest path with negative edges
   Complexity:  bellman O(VE)

   Details: May be used to detect negative cycles reacheble from the source.
   	One may write an optimized version using queue.

	One may detect a negative product cycle by applying log() to the cost of the edges.

	One May convert it to a full DP to find the min cost path with a number of edges
*/

const int INF = 0x3f3f3f3f;   
const int MAXN = 2e3 + 10;

int n, m, dist[MAXN];
vii adj[MAXN];

int bellman(int src){
	for (int i = 1; i <= n; i++)
		dist[i] = INF;
	
	dist[src] = 0;

	for (int k = 0; k < n; k++)
		for (int i = 1; i <= n; i++)
			if (dist[i] < INF)
				for (auto x : adj[i])
					dist[x.fst] = min(dist[x.fst], dist[i] + x.snd);

	for (int i = 1; i <= n; i++)
		for (auto x : adj[i])
			if (dist[i] < INF)
				if (dist[x.fst] > dist[i] + x.snd)
						return -1;

	return 0;
}

int nvis[MAXN];
bool is_in[MAXN];

int bellman_queue(int src){
	for (int i = 1; i <= n; i++){
		dist[i] = INF;
		nvis[i] = 0;
	}

	queue<int> fila;

	fila.push(src);	
	dist[src] = 0;

	while (!fila.empty()){
		int v = fila.front();
		fila.pop();
		is_in[v] = 0;
		nvis[v]++;

		if (nvis[v] > n)
			return -1;

		for (auto x : adj[v])
			if (dist[v] + x.snd < dist[x.fst]){
				dist[x.fst] = dist[v] + x.snd;
				if (!is_in[x.fst]){
					is_in[x.fst] = 1;
					fila.push(x.fst);
				}
			}
	}

	return 0;
}