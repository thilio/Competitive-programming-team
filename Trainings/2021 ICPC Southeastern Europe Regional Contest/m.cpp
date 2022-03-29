#include "bits/stdc++.h"
using namespace std;

#define fr(i, n) for(ll i = 0; i < n; i++)
#define frr(i, n) for(ll i = 1; i <= n; i++)
#define gnl cout<<endl
#define dbg(x) cout<<#x<< " = "<<x<<endl
#define olar cout<<"olar"<<endl
#define all(x) x.begin(),x.end()
#define pb push_back

#define f first
#define s second

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> pii;

const ll MAXN = 400010;

vector<array<ll, 3>> v[MAXN];

ll fastxp(ll base, ll exp, ll mod){
    ll ans = 1;
    while(exp){
        if(exp%2){
            ans = (ans * base) % MOD;
        }
        exp /= 2;
        base = base * base % MOD;
    }
    return ans;
}

ll ans[MAXN];
ll fat[MAXN], ifat[MAXN];
ll p, n;

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> p;
    fat[0] = 1;
    frr(i, MAXN - 1) fat[i] = i * fat[i - 1] % p, ifat[i] = fastxp(fat[i], p - 2, p);
    for(ll i = 2; i < MAXN; i++){
        v[i].pb({i, 1, 1});
        vector<int> div1, div2;
        for(int j = 1; j * j <= i; j++){
            if(i%j == 0){
                div1.pb(i);
                if(j * j != i) div2.pb(i / j);
            }
        }
        reverse(all(div2));
        for(auto x : div2) div1.pb(x);

        for(auto d : div1){
            for(auto y : v[i / d]){
                v[i].pb({y[0] + d, y[1] + 1, });
            }
        }
    }
}