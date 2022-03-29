#include "bits/stdc++.h"
using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
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

int a, b, c, n;
int x, y, z;
string s;
set<int> va, vc;
vector<pii> ans;

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    cin >> s;
    for(auto x : s){
        if(x == 'A') a++;
        else if(x == 'B') b++;
        else c++;
    }

    z = n - a, y = n - b, x = n - c;
    if(x < 0 || y < 0 || z < 0){
        cout << "NO" << endl;
        return 0;
    }

    fr(i, 2 * n){
        if(s[i] == 'A') va.insert(i);
        else if(s[i] == 'C') vc.insert(i);
    }

    int tot_b = 0;
    fr(i, 2 * n){
        if(s[i] == 'B'){
            if(tot_b == z) {
                auto it = va.lower_bound(i);
                if(va.size() == 0 || it == va.begin()){
                    cout << "NO" << endl;
                    return 0;
                }
                it--;
                ans.pb({*it, i});
                va.erase(it);
            }
            else {
                auto it = vc.lower_bound(i);
                if(it == vc.end()){
                    cout << "NO" << endl;
                    return 0;
                }
                ans.pb({i, *it});
                
                vc.erase(it);
                tot_b++;
            }
        }
    }

    assert(va.size() == vc.size());

    while(va.size()){
        if(*(va.begin()) >= *(vc.begin())){
            cout << "NO" << endl;
            return 0; 
        }
        ans.pb({*(va.begin()), *(vc.begin())});
        va.erase(va.begin());
        vc.erase(vc.begin());
    }

    assert(ans.size() == n);

    cout << "YES" << endl;
    for(auto x : ans) cout << x.f + 1 << " " << x.s + 1 << endl;
}