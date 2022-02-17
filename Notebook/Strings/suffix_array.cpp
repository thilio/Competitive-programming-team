/* 
	Title: Suffix array
	Description: Algorithm to sort the suffix of a given array(string)
	Complexity: O(n log(n))
	Details: It may be easily changed to handle vector<int> instead of string
*/

struct suffixArray{
	int n, len, h/*Coordinate compression and LCP*/;
	vector<int> sa, r/*rank*/, lcp, aux, cnt;

	void countingSort(vector<int> & p, int len){
		fill(cnt.begin(), cnt.end(), 0);
		for(int & x : p) 
			cnt[r[x] + 1]++, x = (x - len + n) % n;
		for(int i = 1; i < n; i++) 
			cnt[i] += cnt[i - 1];
		for(int x : p) 
			aux[cnt[r[x]]++] = x;
		p = aux;
	}

	suffixArray(string s = ""){
		s.push_back('$'), n = s.size(), len = 1, h = 0;
		sa.resize(n), r.resize(n), lcp.resize(n), aux.resize(n), cnt.resize(n + 1);
		
		// Coordinate compression
		map<int, int> m; for(int x : s) m[x] = 1;
		for(auto & x : m) x.second = h++;
		for(int i = 0; i < n; i++) r[i] = m[s[i]], sa[i] = i;
		
		countingSort(sa, 0);
		while(len < n){
			countingSort(sa, len), aux[sa[0]] = 0;
			// Build new classes
			for(int i = 1; i < n; i++) 
				aux[sa[i]] = aux[sa[i - 1]] + /*Not equal to previous*/\
				(r[sa[i]] != r[sa[i - 1]] || r[(sa[i] + len)%n] != r[(sa[i - 1] + len)%n]); 
			r = aux, len <<= 1;	
		}

		// Build LCP
		h = 0;
		for(int i = 0; i < n; i++){
			if(r[i] > 0){
				int j = sa[r[i] - 1];
				while(s[i + h] == s[j + h]) h++;
				lcp[r[i]] = h;
				if(h > 0) h--;
			}
		}	
	}
};

struct RMQ{
    int N = 0;
    vector<vector<int>> t;
    inline int op(int& a, int& b) { return min(a, b); }
    RMQ() {}
    RMQ(vector<int>& v) : N(int(v.size())), t(__lg(N) + 1) {
        t[0].resize(N);
        for (int i = 0; i < N; ++i) t[0][i] = v[i];
        for (int a = 1; a < int(t.size()); ++a) {
            t[a].resize(N - (1 << a) + 1);
            for (int b = 0; b + (1 << a) <= N; ++b)
                t[a][b] = op(t[a-1][b], t[a-1][b + (1 << (a-1))]);
        }
    }
    int query(int a, int b) {
        int lg = __lg(b - a + 1);
        return op(t[lg][a], t[lg][b - (1 << lg) + 1]);
    }
};