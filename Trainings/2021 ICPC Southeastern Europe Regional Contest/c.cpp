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

#define f first
#define s second

typedef long long int ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int MAXN = 3030;
const int MOD = 998244353;

ll cor[MAXN], w[MAXN];
ll ans;
vi adj[MAXN];
ll v[MAXN][2*MAXN];
ll aux[2*MAXN];
ll l[MAXN], r[MAXN];
ll n, f;

void dfs(int vtx, int p = -1){
       
    bool folha = true;
    for(auto x: adj[vtx]){
        if(x != p){
            dfs(x, vtx);
            folha = false;
        }
    }
    if(folha){
        
        if(w[vtx] == 1){
            v[vtx][f + 1] = 1;
            l[vtx] = f + 1; r[vtx] = f + 1;
        }
        else{
            v[vtx][f - 1] = 1;
            l[vtx] = f - 1; r[vtx] = f - 1;
        }
        return;
    }
    else{
        bool ja = false;
        fr(k, adj[vtx].size()){
            if(adj[vtx][k] == p) continue;
            int x = adj[vtx][k];
            if(!ja){
                ja = true;
                
                v[x][f]++;
                for(int i = 0; i <= 2*f; i++) if(i + w[vtx] >= 0) v[vtx][i + w[vtx]] = v[x][i];
                v[x][f] += MOD - 1;
                l[vtx] = max(l[x] + w[vtx], (ll)0); r[vtx] = min(r[x] + w[vtx], 2*f);

                l[vtx] = min(l[vtx], f + w[vtx]);
                r[vtx] = max(r[vtx], f + w[vtx]);
            }
            else{
                for(int i = 0; i <= 2*f; i++) aux[i] = 0;
                v[x][f]++;
                l[x] = min(l[x], f);
                r[x] = max(r[x], f);
                for(int i = l[vtx]; i <= r[vtx]; i++){
                    for(int j = l[x]; j <= r[x]; j++){
                        if(i + j - f > 2*f) break;
                        if(i + j  < f) continue;
                        aux[i + j - f] = (aux[i + j - f] + v[vtx][i]*v[x][j])%MOD;
                      
                    }
                }
                v[x][f] = (v[x][f] + MOD - 1)%MOD;
                for(int i = 0; i <= 2*f; i++) v[vtx][i] = aux[i];
                l[vtx] = max(l[vtx] + l[x] - f,(ll) 0);
                r[vtx] = min(r[vtx] + r[x] - f, 2*f);
            }
        }
    }
}

void solve(int c){
    f = 0;
    frr(i, n){
        if(cor[i] == c){
            f++;
            w[i] = 1;
        }
        else
            w[i] = -1;
    }

    frr(i, n){
        fr(j, 2*f + 1) v[i][j] = 0;
    }
    
    if(f == 0) return;

    dfs(1);

  //  fr(i, 2*f + 1) dbg(v[1][i]);
    //gnl;

    frr(u, n){
        for(int i = 1; i <= f; i++){
            ans += v[u][f + i];
            ans %= MOD;
        }
    }

    

}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;

    if(n == 1){
        cout << 1 << endl;
        return 0;
    }

    frr(i, n) cin >> cor[i];

    fr(i, n - 1){
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    frr(i, n){
        solve(i);
    }

    cout << (ans%MOD + MOD)%MOD<< endl;

    

}