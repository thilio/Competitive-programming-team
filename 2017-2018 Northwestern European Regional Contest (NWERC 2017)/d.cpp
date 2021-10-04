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
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

ll n, m;
vector<string> s;

map<string, ll> cor, inc;
map<string, string> tran;

signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n;

	s.resize(n);
	fr(i, n){
		cin>>s[i];
	}


	cin>>m;
	string t[3];

	fr(i, m){
		cin>>t[0]>>t[1]>>t[2];
		
		tran[t[0]] = t[1];

		if (t[2] == "correct")
			cor[t[0]]++;
		else
			inc[t[0]]++;

	}

	bool ok = 1;

	for (auto x : s)
		if (cor[x] + inc[x] > 1)
			ok = 0;

	if (ok){
		ok = 1;
		for (auto x : s){
			if (inc[x] > 0) ok = 0;
			cout<<tran[x]<<' ';
		}
		gnl;

		cout<<(ok? "correct" : "incorrect")<<endl;
		return 0;
	}

	ll tot = 1, crt = 1;

	for (auto x : s){
		ll y = cor[x];

		crt *= y; // todas corretas

		y += inc[x];

		tot *= y; // todas as possibilidades
	} 

	cout<<crt<<" correct"<<endl;
	cout<<(tot - crt)<<" incorrect"<<endl;
}