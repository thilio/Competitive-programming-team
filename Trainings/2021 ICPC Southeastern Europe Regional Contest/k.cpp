#include "bits/stdc++.h"
using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define endl '\n'
#define gnl cout<<endl
#define dbg(x) cout<<#x<< " = "<<x<<endl
#define olar cout<<"olar"<<endl
#define all(x) x.begin(),x.end()
#define pb push_back

#define fst first
#define snd second

typedef long long int ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int MAXN = 2e5 + 10;

int n;
vi adj[MAXN];
vector<pair<int, int>> sub[MAXN];

int dfs_sub(int v, int p){
    sub[v].clear();

    for (auto x : adj[v])
        if (x != p){
            int a = dfs_sub(x, v);
            sub[v].pb({a, x});
        }

    sort(all(sub[v]));

    if (sub[v].empty())
        return v;    

    return sub[v][0].fst;
}

int dfs_root(int v, int p){
    if (sub[v].empty())
        return v;

    if (sub[v].back().fst > v)
        return dfs_root(sub[v].back().snd, v);

    return v;
}

vi ans;

void dfs_ans(int v, int p){

    for (auto x : sub[v])
        dfs_ans(x.snd, v);

    ans.pb(v);
}

void solve(){
    cin>>n;

    frr(i, n)
        adj[i].clear();

    fr(i, n - 1){
        int a, b;
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    int small_leaf = n + 1;

    frr(i, n)
        if (adj[i].size() == 1) // this is a leaf
            small_leaf = min(small_leaf, i);

    dfs_sub(small_leaf, small_leaf);
    int r = dfs_root(adj[small_leaf][0], small_leaf);

    dfs_sub(r, r);

    ans.clear();
    dfs_ans(r, r);

    for (auto x : ans)
        cout<<x<<' ';
    gnl;
}


signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int T;
    cin>>T;
    while (T--)
        solve();
}