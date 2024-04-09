/*
    Title: Lowest common ancestor using binary lifting
    Descripition: given a tree, find the lowest common ancestor of two vertices
    Complexity: 
        - LCA() : O(n log n)
        - lca(int a, int b) : O(log n)
        - dist(int a, int b) : O(log n)
        - kth(int v, int k) : O(log n)
    Details:
        "kth" function returns the k-th element in the path between v and the root

    Credits: https://cp-algorithms.com/graph/lca_binary_lifting.html 
*/

struct LCA{
    int n, maxl, tempo = 0;
    vector<int> tin, tout, h;
    vector<vector<int>> adj, anc;

    void dfs(int v, int pai){
        h[v] = h[pai] + 1, anc[v][0] = pai;
        for(int i = 1; i <= maxl; i++) anc[v][i] = anc[anc[v][i-1]][i-1];
        
        tin[v] = tempo++;
        for(int u: adj[v]) if(u != pai) dfs(u, v);
        tout[v] = tempo++;
    }

    bool is_ancestor(int v, int u){
        return (tin[v] <= tin[u] && tout[v] >= tout[u]);
    }

    int lca(int a, int b){
        if(is_ancestor(a, b)) return a;
        if(is_ancestor(b, a)) return b;

        for (int i = maxl; i >= 0; --i) 
            if (!is_ancestor(anc[a][i], b))
                a = anc[a][i];

        return anc[a][0];
    }

    int dist(int a, int b){
        int l = lca(a, b);
        return h[a] + h[b] - 2*h[l];
    }

    /*Retorna o k-ésimo elemento no caminho de v até a raiz*/
    int kth(int v, int k){
        k--;
        for(int i = maxl; i >= 0; i--)
            if((1 << i) <= k)
                k -= (1 << i), v = anc[v][i];

        return v;
    }

    LCA(): n(0) {};
    LCA(int vtx, vector<int> a[]){
        n = vtx, maxl = ceil(log2(n)), tempo = 0;
        tin.resize(n+1, 0), tout.resize(n+1, 0), h.resize(n+1, 0);
        adj.resize(n+1), anc.resize(n+1);

        for(int i = 1; i <= n; i++) 
            adj[i] = a[i], anc[i].resize(maxl + 1);

        dfs(1, 1);
    }
};