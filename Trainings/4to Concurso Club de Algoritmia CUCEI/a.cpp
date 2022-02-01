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

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	ll n, m, x;
	cin>>n>>m>>x;

	vector<pair<ll, ll>> v;

	ll typ, l, r;
	fr(i, m){
		cin>>typ>>l>>r;
		if (typ == 1)
			v.pb({l, r});
		else{
			if (l > 1)
				v.pb({1, l - 1});
			if (r < n)
				v.pb({r + 1, n});
		}
	}

	set<pair<ll, ll>> q;
	q.insert({x, 0});

	ll lft, rgt, p, d;
	for (auto b : v){
		tie(l, r) = b;
		lft = rgt = llINF;

		while (q.lower_bound({l, -1}) != q.end()){
			auto it = q.lower_bound({l, -1});
			if ((*it).fst > r)
				break;
			p = (*it).fst;
			d = (*it).snd;
			q.erase(it);
			lft = min(lft, d + abs(l - p));
			rgt = min(rgt, d + abs(r - p));
		}
		if (lft < llINF and l > 1)
			q.insert({l - 1, lft + 1});
		if (rgt < llINF and r < n)
			q.insert({r + 1, rgt + 1});
	}

	if (q.empty()){
		cout<<-1<<endl;
		return 0;
	}

	ll ans = llINF;
	while (!q.empty()){
		ans = min(ans, (*q.begin()).snd);
		q.erase(q.begin());
	}

	cout<<ans<<endl;
}