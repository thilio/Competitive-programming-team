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
const int MAXN = 510;

typedef tuple<ll, ll, ll> tup;

ll n, m, xs, ys, xt, yt;
ll a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN][MAXN], w[MAXN][MAXN];

ll dist[MAXN][MAXN];

ll move_x(ll tme, ll x, ll y){
	ll va = a[x][y];
	ll vb = b[x][y];

    ll bst = tme/(va + vb);

	if (tme < (bst + 1)*va + bst*vb)
		return tme;
	return (bst + 1)*(va + vb);
}

ll move_y(ll tme, ll x, ll y){
	ll va = a[x][y];
	ll vb = b[x][y];
	
	if (tme < va)
		return va;

	ll bst = (tme-va)/(va + vb);
	
	if (tme < (bst + 1)*(va +vb))
		return tme;
	return (bst + 2)*va + (bst + 1)*vb;
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>m>>xs>>ys>>xt>>yt;

	frr(i, n)
		frr(j, m)
			cin>>a[i][j];
	frr(i, n)
			frr(j, m)
				cin>>b[i][j];
	frr(i, n)
			frr(j, m - 1)
				cin>>c[i][j];
	frr(i, n - 1)
			frr(j, m)
				cin>>w[i][j];


	memset(dist, -1, sizeof dist);			
	priority_queue<tup, vector<tup>, greater<tup> > pq;

	pq.push({0, xs, ys});

	ll dst;
	ll x, y;
	while (!pq.empty()){
		tie(dst, x, y) = pq.top();
		pq.pop();

		if (dist[x][y] == -1){
			dist[x][y] = dst;

			ll tme = move_x(dst, x, y);

			if (x - 1 > 0 and dist[x - 1][y] == -1) pq.push({tme + w[x - 1][y], x - 1, y});
			if (x + 1 <= n and dist[x + 1][y] == -1) pq.push({tme + w[x][y], x + 1, y});

			tme = move_y(dst, x, y);

			if (y - 1 > 0 and dist[x][y - 1] == -1) pq.push({tme + c[x][y - 1], x, y - 1});	
			if (y + 1 <= m and dist[x][y + 1] == -1) pq.push({tme + c[x][y], x, y + 1});	
		}
	}

				
	cout<<dist[xt][yt]<<endl;
}