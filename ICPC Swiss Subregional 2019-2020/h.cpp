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
const int MAXN = 1e5 + 10;

map<__int128, string> mapa;
__int128 pot[500];


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	__int128 pwr = 1;
	for (char a = 'a'; a <= 'z'; a++){
		pot[a] = pwr;
		pwr = pwr * ((__int128) 10);
	}

	int n;
	cin>>n;

	__int128 frq = 0;
	string s;
	fr(i, n){
		frq = 0;
		cin>>s;
		for (char x : s)
			frq += pot[x];

		if (!mapa.count(frq))
			mapa[frq] = s;
		else
			mapa[frq] = min(mapa[frq], s);
	}

	int q, sz;
	cin>>q;

	string t, aux;
	while (q--){
		t.clear(); // resposta vazia

		cin>>s;
		sz = s.size();

		// dbg(s);
		for (int mask = 1; mask < (1<<sz); mask++){
			frq = 0;
			for (int i = 0; i < sz; i++)
				if (mask & (1 << i))
					frq += pot[s[i]];

			// dbg((ll) frq);	
			if (mapa.count(frq)){
				aux = mapa[frq];
				if (aux.size() > t.size()){
					t = aux;
				}
				else if (aux.size() == t.size()){
					t = min(t, aux);
				}
			}
		}

		if (t.empty()) // nada encaixa
			cout<<"IMPOSSIBLE"<<endl;
		else
			cout<<t<<endl;
	}
}