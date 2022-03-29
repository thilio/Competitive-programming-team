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


signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    ll ans = 0, n;
    vector<ll> v;

    cin>>n;

    fr(i, 2 * n){
        ll a, b;
        cin>>a>>b;
        ans -= min(a, b);
        v.pb(a + b);
    }

    sort(all(v));
    reverse(all(v));

    fr(i, n){
        ans += v[i];
    }

    cout<<ans<<endl;
}