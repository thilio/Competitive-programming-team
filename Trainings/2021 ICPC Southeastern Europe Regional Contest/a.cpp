#include "bits/stdc++.h"
using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define endl '\n'
#define gnl cout<<endl
#define dbg(x) cout<<#x<< " = "<<x<<endl
#define olar cout<<"olar"<<endl
#define all(x) x.begin(),x.end()

typedef long long int ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int MAXN = 200010;

int n;
string s, t;
int nxt[MAXN];
int v[MAXN];

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> s >> t;

    fr(i, n){
        if(s[i] == t[i]) v[i] = 0;
        else if(s[i] < t[i]) v[i] = -1;
        else v[i] = 1;
    }

    v[n] = 1;
    nxt[n] = n;
    for(int i = n - 1; i >= 0; i--){
        if(v[i] != 0) nxt[i] = i;
        else nxt[i] = nxt[i + 1];
    }

    ll ans = 0;
    fr(i, n){
        if(v[i] == -1) ans += (ll)(n - i);
        else if(v[i] == 0){
            if(v[nxt[i]] == -1){
                ans += (ll)(n - nxt[i]);
            }
        }
    }

    cout << ans << endl;
}