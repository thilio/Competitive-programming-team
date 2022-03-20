/*
    Title: Range minimum query
    Description: Data structure to get queries in range in O(1)
    Complexity:
        - O(n log(n)) to build
        - O(n log(n)) in memory
        - O(1) per query
*/
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
                t[a][b] = op(t[a-1][b], t[a-1][b + (1 << (a - 1))]);
        }
    }
    int query(int a, int b) {
        int lg = __lg(b - a + 1);
        return op(t[lg][a], t[lg][b - (1 << lg) + 1]);
    }
};