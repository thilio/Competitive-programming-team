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

int h, w, n;

void print(int x, int y){
    vector<string> ans;
    ans.resize(h);
    fr(i, h){
        ans[i].resize(w);
        fr(j, w)
            ans[i][j] = '.';
    }

    x--; // numero de barreiras
    y--;

    int p = 1;
    while (x > 0){
        x--;
        fr(j, w)
            ans[p][j] = '#';
        p += 2;    
    }  

    p = 1;
    while(y > 0){
        y--;
        fr(i, h)
            ans[i][p] = '#';
        p += 2;    
    }

    fr(i, h){
        fr(j, w)
            cout<<ans[i][j];
        gnl;    
    }

    exit(0);
}

signed main(){
    fastio;
    freopen("kotlin.in", "r", stdin);
    freopen("kotlin.out", "w", stdout);

    cin>>h>>w>>n;

    for (int i = 1; i <= (h + 1)/2; i++)
        for (int j = 1; j <= (w + 1)/2; j++)
            if (i * j == n)
                print(i, j);

    cout<<"Impossible"<<endl;
}