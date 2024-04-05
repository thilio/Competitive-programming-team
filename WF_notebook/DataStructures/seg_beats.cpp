/*
    Title: Segtree beats
    Description: Segment tree with operations
    			 (1) a[i] -> max(a[i], x), i in [l, r]
    			 (2) a[i] -> min(a[i], x), i in [l, r]
    			 (3) a[i] -> a[i] + x, i in [l, r]
    			 and query
    			 sum a[i], i in [l, r]
    Complexity: Build O(n), query O(log n), updatemin/max O(log n) amortized
    			updatesum O(log^2 n)
    Details: 0-indexed; updatemin/max makes updates (1) and (2);
    		 updatesum make update (3); query returns {min, max, sum}	*/
const long long int llINF = 0x3f3f3f3f3f3f3f;
namespace beats {
	struct node {
		int tam;
		long long int sum, lazy; // lazy pra soma
		long long int mi1, mi2, mi; // mi = #mi1
		long long int ma1, ma2, ma; // ma = #ma1

		node(long long int x = 0) {
			sum = mi1 = ma1 = x;
			mi2 = llINF, ma2 = -llINF;
			mi = ma = tam = 1;
			lazy = 0;
		}
		node(const node& l, const node& r) {
			sum = l.sum + r.sum, tam = l.tam + r.tam;
			lazy = 0;
			if (l.mi1 > r.mi1) {
				mi1 = r.mi1, mi = r.mi;
				mi2 = min(l.mi1, r.mi2);
			} else if (l.mi1 < r.mi1) {
				mi1 = l.mi1, mi = l.mi;
				mi2 = min(r.mi1, l.mi2);
			} else {
				mi1 = l.mi1, mi = l.mi+r.mi;
				mi2 = min(l.mi2, r.mi2);
			}
			if (l.ma1 < r.ma1) {
				ma1 = r.ma1, ma = r.ma;
				ma2 = max(l.ma1, r.ma2);
			} else if (l.ma1 > r.ma1) {
				ma1 = l.ma1, ma = l.ma;
				ma2 = max(r.ma1, l.ma2);
			} else {
				ma1 = l.ma1, ma = l.ma+r.ma;
				ma2 = max(l.ma2, r.ma2);
			}
		}
		void setmin(long long int x) {
			if (x >= ma1) return;
			sum += (x - ma1)*ma;
			if (mi1 == ma1) mi1 = x;
			if (mi2 == ma1) mi2 = x;
			ma1 = x;
		}
		void setmax(long long int x) {
			if (x <= mi1) return;
			sum += (x - mi1)*mi;
			if (ma1 == mi1) ma1 = x;
			if (ma2 == mi1) ma2 = x;
			mi1 = x;
		}
		void setsum(long long int x) {
			mi1 += x, mi2 += x, ma1 += x, ma2 += x;
			sum += x*tam;
			lazy += x;
		}
	};

	node seg[4*MAXN];
	int n;
	vector<long long int> v;

	node build(int p=1, int l=0, int r=n-1) {
		if (l == r) return seg[p] = {v[l]};
		int m = (l+r)/2;
		return seg[p] = {build(2*p, l, m), build(2*p+1, m+1, r)};
	}
	void build(int n2, vector<long long int> v2) {
		n = n2, v = v2;
		build();
	}
	void prop(int p, int l, int r) {
		if (l == r) return;
		for (int k = 0; k < 2; k++) {
			if (seg[p].lazy) seg[2*p+k].setsum(seg[p].lazy);
			seg[2*p+k].setmin(seg[p].ma1);
			seg[2*p+k].setmax(seg[p].mi1);
		}
		seg[p].lazy = 0;
	}
	array<long long int, 3> query(int a, int b, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a) return {llINF, -llINF, 0};
		if (a <= l and r <= b) return {seg[p].mi1, seg[p].ma1, seg[p].sum};
		prop(p, l, r);
		int m = (l+r)/2;
		auto L = query(a, b, 2*p, l, m), R = query(a, b, 2*p+1, m+1, r);
		return {min(L[0], R[0]), max(L[1], R[1]), L[2]+R[2]};
	}
	node updatemin(int a, int b, long long int x, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a or seg[p].ma1 <= x) return seg[p];
		if (a <= l and r <= b and seg[p].ma2 < x) {
			seg[p].setmin(x);
			return seg[p];
		}
		prop(p, l, r);
		int m = (l+r)/2;
		return seg[p] = {updatemin(a, b, x, 2*p, l, m),
						updatemin(a, b, x, 2*p+1, m+1, r)};
	}
	node updatemax(int a, int b, long long int x, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a or seg[p].mi1 >= x) return seg[p];
		if (a <= l and r <= b and seg[p].mi2 > x) {
			seg[p].setmax(x);
			return seg[p];
		}
		prop(p, l, r);
		int m = (l+r)/2;
		return seg[p] = {updatemax(a, b, x, 2*p, l, m),
						updatemax(a, b, x, 2*p+1, m+1, r)};
	}
	node updatesum(int a, int b, long long int x, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a) return seg[p];
		if (a <= l and r <= b) {
			seg[p].setsum(x);
			return seg[p];
		}
		prop(p, l, r);
		int m = (l+r)/2;
		return seg[p] = {updatesum(a, b, x, 2*p, l, m),
						updatesum(a, b, x, 2*p+1, m+1, r)};
	}
};