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

int num[30][30];
string s;
int n;

bool is_cons(char c){
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' || c == 'w') return false;
    return true;
}

map<char, int> ind;
int r_ind[30];

int test(int mask){
    int ret = 0;
    fr(i, 19) {
        fr(j, i + 1){
            if(((1 << i)&mask) && (((1 << j)&mask) == 0)) ret += num[j][i];
            if(((1 << j)&mask) && (((1 << i)&mask) == 0)) ret += num[j][i];
        }
    }
    //if(ret) cout << mask << endl;
    return ret;
}

signed main(){
    fastio;
    freopen("consonant.in", "r", stdin);
    freopen("consonant.out", "w", stdout);
    
    int con = 0;
    fr(i, 26){
        if(is_cons('a' + i)) {
            ind['a' + i] = con;
            r_ind[con] = i;
            con++;
        }
    }
    
    cin >> s;
    n = s.size();
    fr(i, n - 1){
        if(is_cons(s[i]) && is_cons(s[i + 1])){
            int l = min(ind[s[i]], ind[s[i + 1]]);
            int r = max(ind[s[i]], ind[s[i + 1]]);
            num[l][r]++;
            //cout << l << " " << r << endl;
        }
    }

    int ans = 0, mask = 0;
    fr(i, (1 << 19)) {
        int aux = test(i);
        if(aux > ans){
            ans = aux;
            mask = i;
        }
    }

    for(auto x : s){
        if(is_cons(x)){
            if((mask&(1 << ind[x]))) cout << (char)(x - 'a' + 'A');
            else cout << x;
        }
        else cout << x;
    }
    cout << endl;
}