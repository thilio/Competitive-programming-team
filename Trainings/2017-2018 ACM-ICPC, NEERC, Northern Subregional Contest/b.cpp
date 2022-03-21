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


string s;
bool up[30], up_neg[30];

bool lo[30], lo_neg[30];


signed main(){
    fastio;
    freopen("boolean.in", "r", stdin);
    freopen("boolean.out", "w", stdout);
    cin >> s;

    int i = 0;
    while(i < s.size()){
        int sig = 1;
        if(s[i] == '~') sig = -1, i++;
        if('A' <= s[i] && s[i] <= 'Z') {
            if(sig == 1) up[s[i] - 'A'] = true;
            else up_neg[s[i] - 'A'] = true;
        }
        else {
            if(sig == 1) lo[s[i] - 'a'] = true;
            else lo_neg[s[i] - 'a'] = true;
        }
        i+=2;   
    }

    int tira = 1, tot = 0;
    fr(i, 26) if(up[i] && up_neg[i]){
        tira = 0;
        break;
    }
    if(tira == 1){
        fr(i, 26) if(lo[i] && lo_neg[i]){
            tira = 0;
            break;
        }
    }

    fr(i, 26) if(up[i] || up_neg[i]) tot++;
    fr(i, 26) if(lo[i] || lo_neg[i]) tot++;

    ll ans = (1ll << tot);
    ans -= tira;

    cout << ans << endl;
}