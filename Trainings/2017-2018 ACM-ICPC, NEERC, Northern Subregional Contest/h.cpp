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

vector<int> adj[MAXN];
int pai[MAXN], n;

vector<int> folhas_livres[MAXN];
int dp[MAXN][2]; // 0 se não peguei e 1 se pequei
int par[MAXN][2];
void dfs_dp(int v, int p){
    for(auto x : adj[v]){
        dfs_dp(x, v);
        if(dp[v][0] + dp[x][0] + 1 >= dp[v][1] + dp[x][1]) 
            par[v][1] = x;
            
        dp[v][1] = max(dp[v][0] + dp[x][0] + 1, dp[v][1] + dp[x][1]);
        dp[v][0] += dp[x][1];
    }
}
void recover_folhas_livres(int v, int peguei, int raiz){
    if(adj[v].size() == 0){
        // é folha
        if(!peguei) folhas_livres[raiz].pb(v);
        return;
    }

    if(!peguei){
        for(auto x : adj[v]){
            recover_folhas_livres(x, (x == par[v][1]), raiz);
        }
    }
    else {
        for(auto x : adj[v]){
            recover_folhas_livres(x, 0, raiz);
        }
    }
}

vector<int> t1, t2;
signed main(){
    fastio;
    // freopen("hidden.in", "r", stdin);
    // freopen("hidden.out", "w", stdout);
    
    cin >> n;
    frr(i, n - 1) cin >> pai[i + 1], adj[pai[i + 1]].pb(i + 1);

    // Constroi os tipos dos caras e as folhas livres
    int ans = 0;
    frr(i, n) if(pai[i] == 0) {
        dfs_dp(i, -1);
        
        ans += dp[i][1];
        if(dp[i][0] != dp[i][1] || i == 1){
            if(i > 1) t1.pb(i);
            recover_folhas_livres(i, 0, i);

            // cout << i << " é t1 ";
            // for(auto x : folhas_livres[i]) cout << x << " ";
            // cout << endl; 
        }
        else{
            t2.pb(i);
            recover_folhas_livres(i, 1, i);
            
            // cout << i << " é t2 ";
            // for(auto x : folhas_livres[i]) cout << x << " ";
            // cout << endl; 
        }
    }

    // Juntei os caras t1 no big boss
    for(auto x : t1){
        pai[x] = 1;
        for(auto f : folhas_livres[x]) folhas_livres[1].pb(f);
    }


    sort(all(t2), [&](int a, int b){
        return folhas_livres[a].size() > folhas_livres[b].size();
    });

    for(auto x : t2){
        if(folhas_livres[1].size()){
            pai[x] = folhas_livres[1].back();
            ans++;
            folhas_livres[1].pop_back();  
        }
        else {
            pai[x] = 1;
            folhas_livres[x].clear();
            recover_folhas_livres(x, 0, x);
            //if(adj[x].size() == 0) folhas_livres[1].pb(x);
        }
        // dbg(x);
        // dbg(folhas_livres[x].size());
        for(auto f : folhas_livres[x]) {
            folhas_livres[1].pb(f);
        }
    }

    cout << ans << endl;
    frr(i, n - 1) cout << pai[i + 1] << " ";
    cout << endl;
}