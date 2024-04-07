//It is ZERO indexed, just make a dummy zero.
namespace seg{
	coord N, t[2 * MAXN];
	void init(int n){ // Index on range [0, N)
		N = n;
		fill(t, t + 2 * (n + 1), NEUT);
	}
	void modify(int p, coord value){ //set value at p
		for (t[p += N] = value; p > 1; p >>= 1)
			t[p>>1] = opr(t[p], t[p^1]);
	}
	coord query(int l, int r) {  // sum on interval [l, r)
		coord res = NEUT;
		for (l += N, r += N; l < r; l >>= 1, r >>= 1){
			if (l & 1) res = opr(res, t[l++]);
			if (r & 1) res = opr(res, t[--r]);
		}
		return res;
	}
}
