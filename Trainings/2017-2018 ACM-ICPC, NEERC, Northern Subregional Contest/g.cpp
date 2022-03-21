#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)

#define endl '\n'
#define gnl cout<<endl
#define olar cout<<"olar"<<endl
#define dbg(x) cout<< #x << " = " << x << endl;
#define all(x) x.begin(), x.end()
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

typedef long long int ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 10;

int n, m;
vi adj[MAXN], ans[3];

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
    for (int i = 1; i <= n; i++){ 
        pre[i] = -1; 
        art[i] = incmp[i] = 0;
    }

    edges.clear();
    blocks.clear();
    tree.clear();
    while (!stk.empty())
        stk.pop();
    
    clk = 0;
    for (int i = 1; i <= n; i++) 
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

    return blocks.size();
}

vi g[MAXN];
bool in_cycle[MAXN], vis[MAXN];
vi path;

int nxt[MAXN], prv[MAXN];

bool dfs_path(int v){
    vis[v] = 1;
    path.pb(v);

    for (auto x : g[v])
        if (!vis[x]){
            if (in_cycle[x]){
                if (!in_cycle[v]){
                    path.pb(x);
                    return true;
                }
                else if (x != prv[v] and x != nxt[v]){
                    path.pb(x);
                    return true;
                }
            }
            else
                if (dfs_path(x))
                    return true;
        }

    path.pop_back();
    return false;
}

vector<int> cycle;

bool dfs_cycle(int v, int p = -1){
    if (p == -1)
        cycle.clear();

    vis[v] = 1;
    cycle.push_back(v);

    for (auto x : g[v])
        if (x != p){
            if (vis[x]){ // My ancestor, found cycle
                reverse(all(cycle));
                while (cycle.back() != x)
                    cycle.pop_back();
                return true;
            }
            else if (dfs_cycle(x, v))
                return true;
        }

    cycle.pop_back();
    return false;
}

void solve_cmp(int id){
    for (auto e : edges[id]){
        g[e.first].pb(e.second);
        g[e.second].pb(e.first);
    }

    for (auto x : blocks[id]){
        in_cycle[x] = 0;
        vis[x] = 0;
    }

    cycle.clear();
    path.clear();

    dfs_cycle(blocks[id].back()); // find cycle
  
    for (int i = 0; i < cycle.size(); i++){ // build cycle adj
        int x = cycle[i];
        int p = cycle[(i + 1) % cycle.size()];
        in_cycle[x] = 1;
        nxt[x] = p;
        prv[p] = x;
    }
   
    for (auto v : blocks[id])
        vis[v] = 0;

    for (auto v : cycle)
        if (g[v].size() > 2){
            dfs_path(v); // start of the path
            break;
        }

    int str = path[0];
    int end = path.back();

    ans[0] = path;

    int l = 0;
    for (int i = 0; i < cycle.size(); i++)
        if (cycle[i] == str)
            l = i;

    int r = 0;
    for (int i = 0; i < cycle.size(); i++)
        if (cycle[i] == end)
            r = i;

    int p = l;
    ans[1].pb(cycle[l]);

    do{
        p = (p + 1) % cycle.size();
        ans[1].pb(cycle[p]);
    } while (p != r);

    p = r;
    ans[2].pb(cycle[p]);

    do{
        p = (p + 1) % cycle.size();
        ans[2].pb(cycle[p]);
    } while (p != l);

    if (ans[1][0] != str)
        reverse(all(ans[1]));
    if (ans[2][0] != str)
        reverse(all(ans[2]));
}

void solve(){
    cin>>n>>m;

    frr(i, n){
        adj[i].clear();
        g[i].clear();
    }

    fr(i, 3)
        ans[i].clear();

    fr(i, m){
        int a, b;
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    int ncmp = find_bcc(n);

    bool ok = 0;    
    for (int i = 0; i < ncmp; i++)
        if (!ok and blocks[i].size() > 3 and blocks[i].size() < edges[i].size()){
            ok = 1;
            solve_cmp(i);
        }    

    if (!ok)
        cout<<-1<<endl;
    else{
        cout<<ans[0][0]<<' '<<ans[0].back()<<endl;
        fr(i, 3){
            cout<<ans[i].size()<<' ';
            for (auto x : ans[i])
                cout<<x<<' ';
                gnl;
        }
    }    
}


signed main(){
    fastio;
    freopen("grand.in", "r", stdin);
    freopen("grand.out", "w", stdout);
    int T;
    cin>>T;
    while (T--)
        solve();
}