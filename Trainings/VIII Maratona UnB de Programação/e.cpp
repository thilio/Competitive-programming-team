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

map<string, int> mapa;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	mapa["Algebra"] = 1;
	mapa["Aritmetica"] = 1;
	mapa["Backtracking"] = 1;
	mapa["Bigint"] = 1;	
	mapa["Combinatoria"] = 1;
	mapa["Estruturas de Dados"] = 1;
	mapa["Geometria"] = 1;
	mapa["Ordenacao"] = 1;
	mapa["Programacao Dinamica"] = 1;
	mapa["SegTrees"] = 1;
	mapa["Teoria dos Numeros"] = 1;
	mapa["Travessia em Grafos"] = 1;

	int n;
	cin>>n;
	
	string ss;
	getline(cin, ss);	

	fr(i, n){
		string s, t;
		getline(cin, s);
		int p = 0;
		while (p < s.size()){
			t.clear();
			while (s[p] != ',' and p < s.size())
				t.pb(s[p++]);
			p++;
			mapa[t]++;
		}
	}

	vector< pair<int, string> > v;
	for (auto it : mapa)
		v.pb({it.snd - 1, it.fst});

	sort(all(v));

	bool ok = 1;
	for (auto x : v)
		if ((v.back().fst - x.fst) * 4 > v.back().fst){
			cout<<"Falta "<<x.snd<<"!"<<endl;
			ok = 0;
		}

	if (ok)
		cout<<"Tudo em Ribas!"<<endl;	
}