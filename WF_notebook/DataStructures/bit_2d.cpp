struct BIT2D{
    vector<vector<int>> bit;
    int n, m;
    // 1-indexed
    BIT2D(vector<vector<int>> a = {}){
        n = a.size(); m = (a.size() ? a[0].size() : 0);
        bit.resize(n + 1);
        for(int i = 0; i <= n; i++) bit[i].resize(m + 1);
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)
            update(i + 1, j + 1, a[i][j]); 
    }
    inline int op(int x, int y) {return x + y;}
    void update(int i, int j, int val){ //  O(log^2 n)
        for(int k = j; k <= n; k += k & (-k))
            for(int l = i; l <= n; l += l & (-l))
                bit[k][l] = op(bit[k][l], val);
    }
    int query(int i, int j){ //  O(log^2 n)
        int sum = 0; // NEUTRAL: if op=min, use sum=INF
        for(int k = j; k > 0; k -= k & (-k))
            for(int l = i; l > 0; l -= l & (-l))
                sum = op(bit[k][l], sum);
        return sum;
    }
    int sum_ret(int x1, int y1, int x2, int y2){
        return query(x2, y2) + query(x1 - 1, y1 - 1) - query(x2, y1 - 1) - query(x1 - 1, y2);
    }
}
