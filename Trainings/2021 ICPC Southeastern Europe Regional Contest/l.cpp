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

int n;
string s;

char solve0(){
    int a = 0, b = 0,c = 0;
    for(auto x : s){
        if(x == 'A') a++;
        else if(x == 'B') b++;
        else c++;
    }
    if(a == n && b == n && c == n){
        cout << 0 << endl;
        exit (0);
    }
    if(a < b && a < c) return 'A';
    else if(c < b && c < b) return 'C';
    else return 'B';
}
void solve2(){
    int a = 0, b = 0, c = 0;

    int i = 1;
    for(auto x : s){
        if(x == 'A') a++;
        else if(x == 'B') b++;
        else c++;
    
        if(a == n){
            cout << 2 << endl;
            cout << i + 1 << " " << 3 * n << " " << 'B' << endl;
            cout << 2 * n + c + 1 << ' ' << 3 * n <<  " " << 'C' << endl;
            exit (0);
        }
        else if(b == n){
            cout << 2 << endl;
            cout << i + 1 << " " << 3 * n << " " << 'A' << endl;
            cout << 2 * n + c + 1 << ' ' << 3 * n <<  " " << 'C' << endl;
            exit (0);
        }
        else if(c == n){
            cout << 2 << endl;
            cout << i + 1 << " " << 3 * n << " " << 'B' << endl;
            cout << 2 * n + a + 1 << ' ' << 3 * n <<  " " << 'A' << endl;
            exit (0);
        }

        i++;
    }
}


vector<int> a, b;
void solve1(char menor){
    fr(i, 3 * n){
        if(s[i] == 'A') a.pb(i);
        else if(s[i] == 'B') b.pb(i);
    }

    int tot_a = 0, tot_b = 0;
    int sobra_a = (int)a.size() - n, sobra_b = (int)b.size() - n;

    if(sobra_a < 0 || sobra_b < 0) return;

    fr(i, 3 * n){
        if(s[i] == 'B') tot_b++;
        else if(s[i] == 'A') tot_a++;
    
        if(tot_a < sobra_a || tot_b < sobra_b) continue;

        int ita = a[tot_a - sobra_a];
        int itb = b[tot_b - sobra_b];

        if(ita > itb){
            if(tot_a == sobra_a){
                cout << 1 << endl;
                cout << itb + 1 << " " << i + 1 << " " << menor << endl;
                exit (0);
            }
            else{
                ita = (a[tot_a - sobra_a - 1]);
                if(ita < itb){
                    cout << 1 << endl;
                    cout << itb + 1 << " " << i + 1 << " " << menor << endl;
                    exit (0);
                }
            }
        }
        else{
            if(tot_b == sobra_b){
                cout << 1 << endl;
                cout << ita + 1 << " " << i + 1 << " " << menor << endl;
                exit (0);
            }
            else{
                itb = (b[tot_b - sobra_b - 1]);
                if(itb < ita){
                    cout << 1 << endl;
                    cout << ita + 1 << " " << i + 1 << " " << menor << endl;
                    exit (0);
                }
            }
        }
    }
}

string aux;
signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> s;
    char menor = solve0();
    if(menor == 'C') solve1(menor);
    else{
        aux = s;
        for(auto & x : s) {
            if(x == menor) x = 'C';
            else if(x == 'C') x = menor;
        }
        solve1(menor);
        s = aux;
    }
    solve2();
}