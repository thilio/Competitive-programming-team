#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

//#define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

ll l, n;
string nome[110];

int32_t main(){
	fastio;
	cin>>l>>n;

	ll p, c, t, r, pos;
	string s, ss;
	vii ans;

	getline(cin, s);
	fr(i, n){
		getline(cin, s);

		pos = 0;
		ss.clear();
		while (s[pos] != ',')
			ss.pb(s[pos++]);
		pos++;
		nome[i] = ss;

		ss.clear();
		while (s[pos] != ',')
			ss.pb(s[pos++]);
		pos++;
		p = stoi(ss);

		ss.clear();
		while (s[pos] != ',')
			ss.pb(s[pos++]);
		pos++;
		c = stoi(ss);

		ss.clear();
		while (s[pos] != ',')
			ss.pb(s[pos++]);
		pos++;
		t = stoi(ss);

		ss.clear();
		while (s[pos] != ',' and pos < s.size())
			ss.pb(s[pos++]);
		r = stoi(ss);

		if (l * (t + r) <= 10080 * t * c)
			ans.pb({p, i});
	}

	sort(all(ans));

	if (ans.empty())
		cout<<"no such mower"<<endl;
	else
		for (auto x : ans)
			if (ans[0].fst == x.fst)
				cout<<nome[x.snd]<<endl;
}