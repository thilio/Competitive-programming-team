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


signed main(){
    fastio;
     freopen("intel.in", "r", stdin);
     freopen("intel.out", "w", stdout);

    int n;
    cin >> n;

    ll ans = 0;
    vector<array<ll, 2>> v;
    v.resize(n);

    ll xmin, ymin;
    xmin = ymin = INF;

    ll xmax, ymax;
    xmax = ymax = -INF;

    fr(i, n){
        cin >> v[i][0] >> v[i][1];

        xmax = max(xmax, v[i][0]);
        xmin = min(xmin, v[i][0]);
        ymax = max(ymax, v[i][1]);
        ymin = min(ymin, v[i][1]);
    }

    
    fr(i, n){
        int prox = (i + 1)%n;

        ans += abs(v[prox][0] - v[i][0]) + abs(v[prox][1] - v[i][1]);
    }


    ans -= 2*((xmax - xmin) + (ymax - ymin));

    cout << ans << endl;
}