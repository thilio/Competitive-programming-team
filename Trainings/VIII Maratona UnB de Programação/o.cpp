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
const int MAXN = 2e3 + 10;

ll n, m, k, l, txt[MAXN][MAXN], pat[66][66];


ll nmtc, match[MAXN]; // # de matches e suas posições 
ll p[MAXN]; // pi[j] é o maior prefixo que tambem é sufixo em s[1:j]
void prefix_func(vector<ll> s){
	for (int i = 1, j = 0; i < s.size(); i++){
		while (j and s[j] != s[i]) 
			j = p[j - 1];
		if (s[j] == s[i]) 
			j++;
		p[i] = j;
	}
}

ll kmp(vector<ll> &t, vector<ll> & s){
	s.pb(-1);
	prefix_func(s);
	s.pop_back();
	nmtc = 0;
	for (int i = 0, j = 0; i < t.size(); i++) {
		while (j and s[j] != t[i]) 
			j = p[j - 1];
		if (s[j] == t[i]) 
			j++;
		if (j == s.size()) 
			match[nmtc++] = i - j + 1;
	}
	return nmtc;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>m>>k>>l;

	string s;
	fr(i, n){
		cin>>s;
		fr(j, m)
			txt[i][j] = (s[j] == '.');
	}

	fr(i, k){
		cin>>s;
		fr(j, l)
			pat[i][j] = (s[j] == '.');
	}

	vector<ll> t;

	for (int j = 0; j < l; j++){ // constoi padrão linear da palavra
		ll x = 0;
		for (int i = k - 1; i >= 0; i--){
			x <<= 1;
			x |= pat[i][j];
		}
		t.pb(x);
	}

	vector<ll> w;
	for (int j = 0; j < m; j++){ // monta texto inicial
		ll x = 0;
		for (int i = k - 1; i >= 0; i--){
			x <<= 1;
			x |= txt[i][j];
		}
		w.pb(x);
	}

	for (int i = k; i < n + 1; i++){
		kmp(w, t);
		if (nmtc != 0){
			cout<< i - k<<' '<< match[0]<<endl;
			return 0;
		}

		if (i < n)
			for (int j = 0; j < m; j++){
				w[j] >>= 1;
				w[j] |= (txt[i][j] << (k - 1));
			}
	}

	cout<<-1<<' '<<-1<<endl;
}