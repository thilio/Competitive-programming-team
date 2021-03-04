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
const int MAXN = 2e3 + 10;

typedef tuple<ll, ll, ll, ll> tup;

ll n, m, v[MAXN], ans[200100];

ll bit[MAXN][MAXN];

void add(int x , int y , ll v){
	for(int i = x ; i < MAXN ; i += (i & -i))
		for(int j = y; j < MAXN ; j += (j & -j))
			bit[i][j] = max(bit[i][j] , v);
}

ll get(int x , int y){
	ll s = -llINF;
	for(int i = x ; i > 0 ; i -= (i & -i))
		for(int j = y; j > 0 ; j -= (j & -j))
			s = max(s, bit[i][j]);
	return s;
}

vector<tup> event, itv;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n>>m;

	v[0] = 0;
	frr(i, n){
		cin>>v[i];
		v[i] += v[i - 1];
	}

	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			itv.pb({v[j] - v[i - 1], i, j, 0});

	ll a, b, u;
	frr(i, m){
		cin>>a>>b>>u;
		event.pb({u, a, b, i});
	}	

	sort(all(itv));
	sort(all(event));

	fr(i, MAXN)
		fr(j, MAXN)
			bit[i][j] = -llINF;

	int p = -1, id, itsz = itv.size();
	for (auto x : event){
		while (p < itsz - 1 and get<0>(itv[p + 1]) <= get<0>(x)){
			p++;
			tie(u, a, b, ignore) = itv[p];
			add(n - a + 1, b, u);
		}

		tie(u, a, b, id) = x;
		ans[id] = get(n - a + 1, b);
	}

	for (int i = 1; i <= m; i++){
		if (ans[i] <= -llINF)
			cout<<"NONE"<<endl;
		else
			cout<<ans[i]<<endl;
	}
}