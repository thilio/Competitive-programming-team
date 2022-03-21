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
const int MXV = 1e6 + 10;
const int MAXN = 4e5 + 10;

int n;
bool in[MXV];
map<int, int> frq;

vector<pii> v, vm;

int ans_mul[MAXN], ans_all[MAXN];

void solve_mul(){ // just need to put in the multiple
    int now = v.size();
    ans_mul[0] = now; // cant do anything

    sort(all(vm));

    // dbg(vm.size());

    int p = 0, sum = 0;

    frr(i, n){
        while (p < vm.size() and sum + vm[p].first <= i){
            now--;
            sum += vm[p].first;
            p++;
        }
        ans_mul[i] = now;
    }
}

void solve_all(){ // now everyone
    int now = v.size();
    ans_all[0] = now;

    sort(all(v));
    for (int i = 1; i <= v[0].first; i++)
        ans_all[i] = now; // didnt do anything yet
    
    int sum = v[0].first; // this one is now the mmc
    // dbg(now);
    int p = 1;
    for (int i = v[0].first + 1; i <= n; i++){
          while (p < v.size() and sum + v[p].first <= i){
            now--;
            sum += v[p].first;
            p++;
        }
        ans_all[i] = now;
    }
    // dbg(p);
    // dbg(sum);
    // dbg(now);
}




signed main(){
    fastio;
    freopen("equal.in", "r", stdin);
    freopen("equal.out", "w", stdout);

    cin>>n;
    fr(i, n){
        int x;
        cin >> x;
        in[x] = 1;
        frq[x]++;
    }

    for (auto e : frq){
        int x = e.first;
        
        int mul = 2 * x;
        bool ok = 0;
        while (mul < MXV){
            if (in[mul])
                ok = 1;
            mul += x;
        }
        
        if (ok)
            vm.pb({e.second, e.first});

        v.pb({e.second, e.first});
    }

    solve_mul();
    solve_all();

    for (int i = 0; i <= n; i++){
        // cout<<ans_mul[i]<<' '<<ans_all[i]<<endl;
        cout<<min(ans_mul[i], ans_all[i])<<' ';
    }
    gnl;
}