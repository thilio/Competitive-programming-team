/*
   Title: Iteractive Segment Tree
   Description: Iteractive Segment Tree
   Complexity:  build O(n)
   		Modify O(log(n))
   		Query O(log(n))
   
   Details: Way faster than recursive with only 2n memory.
   Is zero indexed and the queries are in the interval (l, r].
   One MUST initialize until 2n+ 2 with neutral elements.

   It is ZERO indexed, just make a dummy zero.

   Credits: https://codeforces.com/blog/entry/18051
*/

const int MAXN = 5e5 + 10;

using coord = ll;
#define NEUT 0
#define opr(a, b) a + b

namespace seg{
	coord N, t[2 * MAXN];

	void init(int n){ // Index on range [0, N)
		N = n;
		fill(t, t + 2 * (n + 1), NEUT);
	}

	void modify(int p, coord value){  // set value at position p
		for (t[p += N] = value; p > 1; p >>= 1) // One may change here to modify a value
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
