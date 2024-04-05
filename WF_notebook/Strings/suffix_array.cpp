/* computes the suffix of a given string O(n log(n))
sa[i] is the starting index of the suffix which
is $i$'th in the sorted suffix array.
The returned vector is of size n+1, and sa[0] = n.
The lcp array contains longest common prefixes for
neighbouring strings in the suffix array:
lcp[i] = lcp(sa[i], sa[i-1]), lcp[0] = 0
The input string must not contain any zero bytes.*/
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
struct SuffixArray {
	vi sa, lcp; // can be used with basic_string<int>
	SuffixArray(string& s,int lim=256){
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j=0,p=0; p<n; j=max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a]==y[b]&&y[a+j]==y[b+j])?p-1 : p++;
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};