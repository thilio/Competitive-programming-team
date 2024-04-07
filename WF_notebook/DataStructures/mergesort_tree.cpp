/*Finds the number of elements <= k in the interval [l, r], 
(or the kth element)
build O(nlog(n)) | query O(log(n)^2) | qry_kth O(log(n)^2) 
Uses O(nlog(n)) memory.*/
int v[MAXN]; // array of elements (use pairs for kth)
vector<int> tree[4 * MAXN];
void build(int nd, int l, int r){
	if (l == r) return tree[nd].push_back(v[l]); 
	//if (l==r) return tree[nd].push_back(v[l].snd); // kth
	int meio = (l + r)/2;
	build(nd<<1, l, meio); build(nd<<1|1, meio + 1, r);
	std::merge(all(tree[nd<<1]), all(tree[nd<<1|1]), 
																back_inserter(tree[nd]));
}
/* query(1, 1(0), n(n-1), ql, qr, val) 
returns the # elements <= val in v[l:r]*/
int query(int nd, int l, int r, int ql, int qr, int val){
	if (qr < l or r < ql) return 0;
	if (ql <= l and r <= qr) 
		return lower_bound(all(tree[nd]), val + 1) 
																			- tree[nd].begin();
	int meio = (l + r)/2;
	return query(nd<<1, l, meio, ql, qr, val) 
							+ query(nd<<1|1, meio + 1, r, ql, qr, val);
}
/*
To find the kth element in v[l:r] modify build. v is a 
sorted vector of pairs {value, original_index}. qry_kth 
retuns the original position of kth element, not its value*/
#error sort the array by {value, original_index}	
/* qry_kth(1, 1(0), n(n-1), ql, qr, val) 
returns the position of the kth element v[l:r]*/
int qry_kth(int nd, int l, int r, int ql, int qr, int val){
	if (l == r) return tree[nd][0]; // ori. pos. of kth ele.
	int fst = lower_bound(all(tree[nd<<1]), ql) 
									- tree[nd<<1].begin(); //left child
	int lst = lower_bound(all(tree[nd<<1]), qr + 1) 
																	- tree[nd<<1].begin();
	int meio = (l + r)/2, amnt = lst - fst;
	if (amnt >= val) return qry_kth(nd<<1,l,meio,ql,qr,val);
	else return qry_kth(nd<<1|1,meio+1,r,ql,qr,val-amnt);
}