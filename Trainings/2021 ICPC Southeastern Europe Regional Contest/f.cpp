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

    ll n, x, R, P, k;
    cin >> n >> x >> R >> P >> k;

    string s;
    cin >> s;

    ll ans = n*x;

    ll cnt = 1;
    for (int i = n - 1; i >= 0; i--){
        if (s[i] == '1')
            ans -= R * cnt;
        cnt++;    
    }

    vector<ll> reg, atk;

    cnt = 1;
    for (int i = n - 1; i >= 0; i--){
        if (s[i] == '1'){
            reg.pb(cnt * (R + P));
        }
        else{
            atk.pb(cnt * P);
        }
        cnt++;
    }

    reverse(all(atk));
    reverse(all(reg));


    ll aux = ans; // tudo atk depois reg

    while (atk.size() > k){
        atk.pop_back();
    }

    for (auto x : atk)
        aux += x;

    ll nreg = 0;
    for (int i = 0; atk.size() + i < k; i++){
        aux += reg[nreg++];
    }

    ans = max(ans, aux);

    while (!atk.empty() and nreg < reg.size()){
        aux -= atk.back();
        atk.pop_back();

        aux += reg[nreg++];

        ans = max(ans, aux);
    }    

    cout << ans << endl;
}