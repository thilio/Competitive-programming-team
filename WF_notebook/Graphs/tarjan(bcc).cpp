/*
   Title: Tarjan-Hopcroft algorithm for biconnected components
   Description: Finds the block cut tree of a graph
   Complexity:  find_bcc O(E + V)
  
   Details: Builds the block cut decomposition of the tree.
   The tree has at most 2m vertices.
   First, one find the edges of a bicconected component. Then vertices. Finally 
   the Tree.
   The function retuns the number of blocks. Be caferul with the tree structure.
   One may ignore parallel edges for the pourpose of fing the vertices.
*/

vector<int> adj[MAXN];
stack<pair<int, int>> stk;
int clk, pre[MAXN], art[MAXN], pos[MAXN], incmp[MAXN];
vector<vector<int>> blocks, tree;
vector<vector<pair<int, int>>> edges;

int dfs_bcc(int v, int p = -1){
    int lo = pre[v] = clk++;
    for (int u : adj[v])
        if (u != p){
            if (pre[u] == -1){
                stk.push({u, v});
                int val = dfs_bcc(u, v);
                lo = min(lo, val);

                if (val >= pre[v]){
                    art[v]++;
                    edges.emplace_back();

                    do {
                        edges.back().push_back(stk.top());
                        stk.pop();
                    } while (edges.back().back() != make_pair(u, v));
                }
            }
            else{
                lo = min(lo, pre[u]);
                if (pre[u] < pre[v])
                    stk.push({u, v});
            }
        }
    if (p == -1 and art[v])
        art[v]--;
    return lo;
}

int find_bcc(int n){
    for (int i = 0; i < n; i++){ 
        pre[i] = -1; 
        art[i] = incmp[i] = 0;
    }

    edges.clear();
    blocks.clear();
    tree.clear();
    while (!stk.empty())
        stk.pop();
    
    clk = 0;
    for (int i = 0; i < n; i++) 
        if (pre[i] == -1) 
            dfs_bcc(i);

    for (auto c : edges){ // Build components using edges
        blocks.emplace_back();
        for (auto x : c){
            if (!incmp[x.first])
                blocks.back().push_back(x.first);
            if (!incmp[x.second])
                blocks.back().push_back(x.second);
            incmp[x.first] = incmp[x.second] = 1;
        }
        for (auto x : c)
            incmp[x.first] = incmp[x.second] = 0;
    }   

    tree.resize(blocks.size());
    for (int i = 0; i < n; i++) 
        if (art[i]){
            pos[i] = tree.size(); 
            tree.emplace_back();
        }

    for (int i = 0; i < blocks.size(); i++) 
        for (int v : blocks[i]){
            if (!art[v]) 
                pos[v] = i; // vertex v is in this block
            else{
                tree[i].push_back(pos[v]); // This articulation point connects these vertices
                tree[pos[v]].push_back(i);
            }
    }

    return blocks.size();
}