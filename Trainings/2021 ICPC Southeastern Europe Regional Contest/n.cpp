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


signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    
    int n;
    cin >> n;

    vector<ll> a(n + 1), b(n + 1), c(n + 1);

    fr(i, n + 1)
        cin >> a[i];

    fr(i,n + 1)
        cin >> b[i];

    for(int i = n; i >= 0; i--){
        if(i == n) c[i] = max(0ll, b[i] - a[i]);
        else{
            c[i] = max(0ll, b[i] + (c[i + 1] + 1)/2 - a[i]);
        }
    }

    ll ans = 0;

    for(int i = 0; i < n; i++){
        if(c[i + 1] > 0){
            int change = (c[i + 1] + 1)/2;
            a[i] -= change;
            ans += change;
            a[i + 1] += 2*change;
        }

        if(a[i] < b[i]){
            cout << -1 << endl;
            return 0;
        }
    }
    if(a[n] < b[n]){
        cout << -1 << endl;
        return 0;
    }

    cout << ans << endl;

    
}