/*
   Title: Directed cycle detection
   Description: Finds a directed cycle or reports that there is none
   Complexity:  find_cycle O(V + E)
   Details: Will detect any directed cycle.
*/

const int MAXN = 5e5;

int n, m, pre[MAXN];
vector<int> adj[MAXN], cycle;

bool dfs_cycle(int v){
	cycle.push_back(v);
	pre[v] = 1;

	for (auto x : adj[v]){
		if (pre[x] == 1){
			reverse(cycle.begin(), cycle.end());
			while (cycle.back() != x)
				cycle.pop_back();
			reverse(cycle.begin(), cycle.end()); // Be careful with edge directions    
			return true;    
		}
		else if (pre[x] == 0 and dfs_cycle(x))
			return true;
	}

	pre[v] = 2;
	cycle.pop_back();

	return false;
}

bool find_cycle(){
	fill(pre, pre + n + 1, 0);
	cycle.clear();

	for (int i = 1; i <= n; i++)
		if (pre[i] == 0 and dfs_cycle(i))
			return true;
	return false;
}