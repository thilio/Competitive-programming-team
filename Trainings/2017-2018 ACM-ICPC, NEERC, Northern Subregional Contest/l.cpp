#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)

#define endl '\n'
#define gnl cout<<endl
#define olar cout<<"olar"<<endl
#define dbg(x) cout<< #x << " = " << x << endl;
#define all(x) = x.begin(), x.end()
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

typedef long long int ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;

ll n;

vector<vector<ll>> resp;

__int128 fast(__int128 x, __int128 k){
    if(k == 0) return 1;
    __int128 ans = fast(x, k/2);
    ans *= ans;
    if(k & 1) ans *= x;
    return ans;
}

ll raiz(ll x, ll k){
    __int128 l = 1;
    __int128 r = (1ll << ((60 + k - 1)/k));

    ll best = -1;

    while(l <= r){
        __int128 m = (l + r)/2;

        if(fast(m, k) <= x){
            best = m;
            l = m + 1;
        }
        else{
            r = m - 1;
        }
    }

    return best;
}

signed main(){
    fastio;
    freopen("little.in", "r", stdin);
     freopen("little.out", "w", stdout);

    cin >> n;

    if(__builtin_popcountll(n) == 1){
        cout << -1 << endl;
        return 0;
    }

    int k = 1;

    while(raiz(n, k) >= 2){
        __int128 t = raiz(n, k);

        ll aux = n;
        vector<ll> tent;
        while(aux%t == 0){
            aux /= t;
            tent.pb(t);
        }
        t++;
        while(aux%t == 0){
            aux /= t;
            tent.pb(t);
        }
        if(aux == 1 && tent.size() == k){
            resp.pb(tent);
        }
        k++;
    }

    cout << resp.size() << endl;

    for(auto x: resp){
        cout << x.size();
        for(auto y: x){
            cout << ' ' << y;
        }
        gnl;
    }

}