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
    freopen("auxiliary.in", "r", stdin);
    freopen("auxiliary.out", "w", stdout);
    int n;
    cin >> n;
    if(n%3 == 0) cout << 7 * (n / 3) << endl;
    else if(n%3 == 2) cout << n / 3 * 7 + 1 << endl;
    else cout << (n - 4) / 3 * 7 + 4 << endl;
}