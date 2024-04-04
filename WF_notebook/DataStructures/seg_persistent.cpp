namespace seg{
	vector<int> seg(1, NEUT), lft(1, 0), rgt(1, 0); 
	int rt(0); // last root 
	void init(){ seg = vector<int>(1, NEUT); lft = vector<int>(1, 0); rgt = vector<int>(1, 0); rt = 0;}
	int new_node(int v, int l = 0, int r = 0){
		seg.pb(v);
		lft.pb(l);
		rgt.pb(r);
		return (int)(seg.size()) - 1;
	}
	int build(int l, int r, int *a){ // put all elements of array on new root rt
		if(l == r)
			return new_node(a[l]);
		
		int m = (l + r)/2;
		int nl = build(l, m, a);
		int nr = build(m + 1, r, a);
		return rt = new_node(oper(seg[nl], seg[nr]), nl, nr);
	}
	int update(int nd, int l, int r, int pos, int val){ // returns the new root
		int ks = new_node(seg[nd], lft[nd], rgt[nd]);
		if (l == r){
			seg[ks] = val;
			return ks;
		}
		
		int m = (l + r)/2, ps;
		if(pos <= m)
			ps = update(lft[nd], l, m, pos, val), lft[ks] = ps; // DO NOT change this
		else 
			ps = update(rgt[nd], m + 1, r, pos, val), rgt[ks] = ps;
		
		seg[ks] = oper(seg[lft[ks]], seg[rgt[ks]]);
		return ks;
	}
	int query(int nd, int l, int r, int ql, int qr){
		if(r < ql or qr < l)
			return NEUT;
		if(ql <= l and r <= qr)
			return seg[nd];
		int m = (l + r)/2;
		return oper(query(lft[nd], l, m, ql, qr), query(rgt[nd], m + 1, r, ql, qr));
	}

	int update(int l, int r, int pos, int val){ return rt = update(rt, l, r, pos, val); } // on last root
} 