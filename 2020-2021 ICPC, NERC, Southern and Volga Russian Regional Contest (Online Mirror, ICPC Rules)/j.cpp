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
const int MAXN = 2e5 + 10;

typedef tuple<ll, ll, ll> tup;

ll n, m, k;

ll id[MAXN], sz[MAXN];

ll find(ll a){
	if (id[a] == a)
		return a;
	return id[a] = find(id[a]);
}

bool merge(ll a, ll b){
	a = find(a);
	b = find(b);

	if (a == b) return 0;
	if (sz[b] > sz[a])
		swap(a, b);
	id[b] = a;
	sz[a] += sz[b];
	return 1;
}


ll kruskal(vector<tup> &edges){
	sort(all(edges));

	ll a, b, c, sum = 0;
	for (auto e : edges){
		tie(c, a, b) = e;

		if (merge(a, b))
			sum += c;
	}

	return sum;
}

void solve(){
	cin>>n>>m>>k;

	vector<tup> A, B;

	fr(i, n + 10){
		id[i] = i;
		sz[i] = 1;
	}

	ll a, b, c, dlt = llINF;
	fr(i, m){
		cin>>a>>b>>c;

		dlt = min(dlt, abs(k - c));

		if (c <= k)
			A.pb({abs(c - k), a, b});
		else
			B.pb({abs(c - k), a, b});
	}

	kruskal(A);

	set<int> q;

	for (int i = 1; i <= n; i++)
		q.insert(find(i));

	if (q.size() == 1)
		cout<<dlt<<endl;
	else
		cout<<kruskal(B)<<endl;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int T;
	cin>>T;
	while (T--)
		solve();
}