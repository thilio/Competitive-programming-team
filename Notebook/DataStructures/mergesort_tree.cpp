/*
   Title: Merge sort tree
   Description: Find the number of elements <= k in the interval [l, r], (or the kth element)
   Complexity:  build O(nlog(n))
		query O(log(n)^2)
		query_kth O(log(n)^2) 
   
   Details: Uses O(nlog(n)) memory.
*/

#define all(x)  x.begin(), x.end()
const int MAXN = 1e5 + 10;

int v[MAXN]; // array of elements (use pairs for kth)
vector<int> tree[4 * MAXN];

void build(int node, int l, int r){
	if (l == r) return tree[node].push_back(v[l]); 
	//if (l == r) return tree[node].push_back(v[l].snd); // for kth element
	int meio = (l + r)/2;
	build(node<<1, l, meio); 
	build(node<<1|1, meio + 1, r);
	std::merge(all(tree[node<<1]), all(tree[node<<1|1]), back_inserter(tree[node]));
}

// query(1, 1(0), n(n-1), ql, qr, val) returns the # elements <= val in v[l:r]
int query(int node, int l, int r, int ql, int qr, int val){
	if (qr < l or r < ql) return 0;
	if (ql <= l and r <= qr) 
		return lower_bound(all(tree[node]), val + 1) - tree[node].begin();
	int meio = (l + r)/2;
	return query(node<<1, l, meio, ql, qr, val) + query(node<<1|1, meio + 1, r, ql, qr, val);
}

/*
  To find the kth element in v[l:r] modify build, such that
  v is a sorted vector of pairs containing {value, original_index}.
  query_kth retuns the original position of kth element, not its value;
*/

#error sort the array by {value, original_index}	
// query_kth(1, 1(0), n(n-1), ql, qr, val) returns the position of the kth element v[l:r]
int query_kth(int node, int l, int r, int ql, int qr, int val){
	if (l == r) return tree[node][0]; // original position of the kth element
	int fst = lower_bound(all(tree[node<<1]), ql) - tree[node<<1].begin(); //left child
	int lst = lower_bound(all(tree[node<<1]), qr + 1) - tree[node<<1].begin();
	int meio = (l + r)/2;
	int amnt = lst - fst; // # of elements in the left childo
	if (amnt >= val) // is in the left child
		return query_kth(node<<1, l, meio, ql, qr, val);
	else
		return query_kth(node<<1|1, meio + 1, r, ql, qr, val - amnt);
}
