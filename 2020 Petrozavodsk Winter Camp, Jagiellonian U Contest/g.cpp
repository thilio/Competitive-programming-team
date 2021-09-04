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

typedef tuple<int, int, int> tup;

void solve(){
	int n;

	cin>>n;

	vector<tup> v;

	int x, y;
	fr(i, n){
		cin>>x>>y;
		v.pb({x, y, 0});
	}	
	fr(i, n){
		cin>>x>>y;
		v.pb({x, y, 1});
	}	

	sort(all(v));

	int hgt = 200;
	vii ans[n];

	int a, b;
	fr(r, n){
		int p = 0;

		while (get<2>(v[p]) == get<2>(v[p + 1]))
			p++; // sempre valido

		tie(x, y, ignore) = v[p];
		tie(a, b, ignore) = v[p + 1];

		ans[r].pb({x, y});
		ans[r].pb({x, hgt});
		ans[r].pb({a, hgt});
		ans[r].pb({a, b});
		
		hgt += 10;

		v.erase(v.begin() + p);
		v.erase(v.begin() + p);
	}


	fr(i, n){
		cout<<ans[i].size()<<endl;
		for (auto e : ans[i])
			cout<<e.fst<<' '<<e.snd<<endl;
	}
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin>>T;

	while (T--)
		solve();
}