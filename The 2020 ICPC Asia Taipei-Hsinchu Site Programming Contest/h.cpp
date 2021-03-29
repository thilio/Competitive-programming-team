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

ll id[MAXN], sz[MAXN];

void init(ll n){
	fr(i, n + 10){
		id[i] = i;
		sz[i] = 1;
	}
}

ll find(ll a){
	if (a == id[a]) return a;
	return id[a] = find(id[a]);
}

bool merge(ll a, ll b){
	a = find(a);
	b = find(b);
	
	if (a == b) return false;
	
	if (sz[a] < sz[b]) swap(a, b);

	id[b] = a;
	sz[a] += sz[b];
	return true;
}

typedef tuple<ll, ll, ll> tup;

vector<tup> edges;

ll n, m;

ll find_bot(){
	init(n);

	reverse(all(edges));
	ll mn = get<0>(edges[0]);

	ll a, b, c;
	for (auto x : edges){
		tie(c, a, b) = x;
		if (merge(a, b))
			mn = c;
	}
	reverse(all(edges));

	return mn;
}


vector<tup> tree;

ll solve(){
	ll mn = find_bot();

	init(n);
	ll a, b, c;
	for (auto x : edges){
		tie(c, a, b) = x;
		if (c >= mn and merge(a, b))
			tree.pb({c, a, b});
	}

	init(n);
	reverse(all(tree));

	ll ans = 0;
	for (auto x : tree){
		tie(c, a, b) = x;
		ans += c * sz[find(a)] * sz[find(b)]; // é uma aresta da arvore, liga componentes
		merge(a, b);
	}

	return ans;
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n>>m;

	ll a, b, c;
	fr(i, m){
		cin>>a>>b>>c;
		edges.pb({c, a, b});
	}

	sort(all(edges));

	cout<<solve()<<endl;
}