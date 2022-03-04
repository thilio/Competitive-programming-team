/*
    Title: Kosaraju's algorythm
    Description: find Strongly Connected Components of a directed graph
    Complexity: O(|V| + |E|)
    Details: Vertices are in range [0...n-1]
        - vector "comp" contains which component each vertex belongs to
        - vector "size" contains the size of each component
*/

#define MAXN 200010

vector <int> g[MAXN], gr[MAXN];
int n, m;

struct KOSARAJU{
    vector<bool> used;
    vector<int> order, comp, size;
    int tot = 0;

    void dfs1 (int v) {
        used[v] = true;
        for (size_t i=0; i<g[v].size(); ++i)
            if (!used[ g[v][i] ]) dfs1 (g[v][i]);
        order.push_back (v);
    }

    void dfs2 (int v, int c) {
        used[v] = true, comp[v] = c, size[c]++;
        for (size_t i=0; i<gr[v].size(); ++i)
            if (!used[ gr[v][i] ]) dfs2 (gr[v][i], c);
    }

    void build(){
        comp.assign(n, -1), size.assign(n, 0), order.clear(), used.assign(n, false);
        for (int i=0; i<n; ++i)
            if (!used[i]) dfs1 (i);

        used.assign (n, false), tot = 0;

        for (int i=0; i<n; ++i) {
            int v = order[n-1-i];
            if (!used[v]) dfs2 (v, tot++);
        }
    }
};

void read(){
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        g[a].push_back (b);
        gr[b].push_back (a);
    }
}

int main() {
    KOSARAJU k;
    read();
    k.build();
}