/* build O(nlog(n)) | update O(log(n)) | query O(log(n))*/
namespace seg{
	vector<int> seg(1, NEUT), lft(1, 0), rgt(1, 0); 
	int rt(0); // last root 
	void init(){
		seg = vector<int>(1, NEUT); 
		lft = vector<int>(1, 0); 
		rgt = vector<int>(1, 0); rt = 0;
	}
	int new_node(int v, int l = 0, int r = 0){
		seg.pb(v); lft.pb(l); rgt.pb(r);
		return (int)(seg.size()) - 1;
	}
	// put all elements of array on new root rt
	int build(int l, int r, int *a){ 
		if(l == r) return new_node(a[l]);
		int m = (l + r)/2;
		int nl = build(l, m, a), nr = build(m + 1, r, a);
		return rt =new_node(oper(seg[nl], seg[nr]), nl, nr);
	}
	// returns the new root
	int update(int nd, int l, int r, int pos, int val){
		int ks = new_node(seg[nd], lft[nd], rgt[nd]);
		if (l == r){ seg[ks] = val; return ks; }
		int m = (l + r)/2, ps;
		if(pos <= m) // DO NOT change this!!!!!!!!!!
			ps = update(lft[nd],l,m,pos,val), lft[ks] = ps; 
		else // DO NOT change this!!!!!!!!!!
			ps = update(rgt[nd],m+1,r,pos,val), rgt[ks]= ps;
		seg[ks] = oper(seg[lft[ks]], seg[rgt[ks]]);
		return ks;
	}
	int query(int nd, int l, int r, int ql, int qr){
		if(r < ql or qr < l) return NEUT;
		if(ql <= l and r <= qr) return seg[nd];
		int m = (l + r)/2;
		return oper(query(lft[nd], l, m, ql, qr), 
						query(rgt[nd], m + 1, r, ql, qr));
	}
	int update(int l, int r, int pos, int val){ // last root
		return rt = update(rt, l, r, pos, val); 
	}
} 