#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   

// Algoritmo de Manacher
// acha todos os palindromos de uma string 
// complexidade : O(n)

using namespace std;
const int MAXN = 1e4 + 10;

int d1[MAXN], d2[MAXN];	// d1[i] # de palindromos impares centrados em i
						// d2[i] # de palindromos pares centrados em i (aab[b]aa) 
						
ll manacher(string &s){
	int tam = s.size();
	for (int i = 0, l = 0, r = -1; i < tam; i++){
		int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
    	while (0 <= i - k and i + k < tam and s[i - k] == s[i + k]) {
    	    k++;
    	}
    	d1[i] = k--;
    	if (i + k > r) {
    	    l = i - k;
		    r = i + k;
		}
	}

	for (int i = 0, l = 0, r = -1; i < tam; i++) {
	    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
	    while (0 <= i - k - 1 and i + k < tam and s[i - k - 1] == s[i + k]) {
	        k++;
	    }
	    d2[i] = k--;
	    if (i + k > r) {
	        l = i - k - 1;
    		r = i + k ;
    	}
	}

	ll ans = 0;
	for (int i = 0; i < tam; i++){
		ans += d1[i];
		ans += d2[i];
	}

	return ans;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	ll ans[MAXN];

	string s, t;

	cin>>n>>s;

	fr(i, n){
		if (s[i] == '-'){
			t.pop_back();
			cout<<ans[t.size()]<<' ';
		}
		else{
			t.pb(s[i]);
			ans[t.size()] = manacher(t);
			cout<<ans[t.size()]<<' ';
		}			
	}
	gnl;
}