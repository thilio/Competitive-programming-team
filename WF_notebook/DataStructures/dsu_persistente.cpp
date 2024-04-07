/*DSU with partial persistance, can only check the past,
For OFFLINE total persistance one may use rollback + dfs.
The time which pairs or vertices were linked is stored. */
int id[MAXN], sz[MAXN], his[MAXN]; 
// his[v] is the time v became descendent
void init(){
	for (int i = 0; i < MAXN; i++) // graph is disjoint at 0
		id[i] = i, sz[i] = 1, his[i] = 0;
}
int find(int a, int t){ // return id[a] in time t O(log(n))
	if (id[a] == a or his[a] > t) return a;
	return find(id[a], t); // DO NOT use path compression
}
void merge(int a, int b, int t){// O(log(n))
	a = find(a, t), b = find(b, t);
	if (a == b) return;
	if (sz[a] < sz[b]) swap(a, b);
	his[b] = t; sz[a] += sz[b]; id[b] = a;
}
int get_time(int a, int b){ // time a united with b or MAXN
	int bst = MAXN, l = 1, r = MAXN, meio;//O(log(t)log(n))
	while (l <= r){
		meio = (l + r)/2;
		if (find(a, meio) != find(b, meio)) l = meio + 1;
		else{ r = meio - 1;bst = meio; }
	}
	return bst;
}