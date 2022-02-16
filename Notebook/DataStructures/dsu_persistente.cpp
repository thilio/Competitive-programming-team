/*
   Title: Persistent Disjoint Set Union
   Description: DSU with partial Persistance
   Complexity:  find O(log(n))
   		merge O(log(n))
   		get_time O(log(time)log(n))
  
   Details: Partial persistance, one may only check the past,
   	    but one shall not change what is done.

   	    For OFFLINE total persistance one may use rollback + dfs.
   
	    The time which pairs or vertices were linked is stored.

*/

const int MAXN = 1e6 + 10;

int id[MAXN], sz[MAXN], his[MAXN]; // his[v] is the time v became descendent

void init(){
	for (int i = 0; i < MAXN; i++){
		id[i] = i;
		sz[i] = 1;
		his[i] = 0; // everybody is disjoint at time 0
	}
}

int find(int a, int t){ // return id[a] in time t
	if (id[a] == a or his[a] > t) 
		return a;
	return find(id[a], t); // DO NOT use path compression
}

void merge(int a, int b, int t){
	a = find(a, t);
	b = find(b, t);
	if (a == b)
		return;
	if (sz[a] < sz[b])
		swap(a, b);
	his[b] = t;
	sz[a] += sz[b];
	id[b] = a;
}

int get_time(int a, int b){ // Retuns time a united with b or MAXN
	int bst, l, r, meio;
	l = 1;
	r = bst = MAXN;

	while (l <= r){
		meio = (l + r)/2;
		if (find(a, meio) != find(b, meio))
			l = meio + 1;
		else{
			r = meio - 1;
			bst = meio;
		}
	}
	return bst;
}
