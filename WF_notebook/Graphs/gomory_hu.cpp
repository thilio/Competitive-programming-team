/* Computes a max-flow equivalent tree
O(|V|(max_flow)), max_flow is maxflow algorithm complexity
Vertices are 1-indexed	   
In a Gomory-Hu tree the minimal capacity in the path from u 
to v equals the max-flow (or min cut) between u and v.*/
int n, m, back_cap[MAXM], pai[MAXN], fpai[MAXN];
int mflow[MAXN][MAXN]; // mflow[u][v] = the max flow 
int cuts[MAXN];// from u to v or -1 if all empty
void find_cut(int v){ // Find a min cut
	cuts[v] = true;
	for (int e = first[v]; e != -1; e = nxt[e])
		if (!cuts[to[e]] and cap[e] > 0)
			find_cut(to[e]);
}
int min_cut(int s, int t){
	memset(cuts, 0, sizeof cuts);
	memcpy(cap, back_cap, sizeof cap);
	int flow = dinic(s, t)
	find_cut(s);			
	return flow;
}
void gomory_hu(){
	memset(mflow, -1, sizeof mflow); // -1 if all empty
	memcpy(back_cap, cap, sizeof cap);
	fill(pai, pai + n + 1, 1);

	for (int s = 2; s <= n; s++){
		int t = pai[s]; 
		fpai[s] = min_cut(s, t);
		mflow[s][t] = mflow[t][s] = fpai[s];
		for (int v = s + 1; v <= n; v++)
			if (cuts[v] and pai[v] == t)
				pai[v] = s;

		for (int v = 1; v < s; v++)
			if (mflow[s][v] == -1){
				int flw = min(mflow[s][t], mflow[t][v]);
				mflow[s][v] = mflow[v][s] = flw;
			}
	}
	memcpy(cap, back_cap, sizeof cap);
}
