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
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e3 + 10;

ll n, m, k, nx, ny;
ll crdx[MAXN], crdy[MAXN]; 
ll memo[MAXN][MAXN];
map<pii, ll> val;

void solve(){
	val.clear();
	cin>>n>>m>>k;

	set<int> qx, qy;
	int x, y;
	fr(i, k){
		cin>>x>>y;
		val[{x, y}] = 1;
		qx.insert(x);
		qy.insert(y);
	}
	qx.insert(0);
	qx.insert(n + 1);
	qy.insert(0);
	qy.insert(m + 1);

	nx = 0;
	while (!qx.empty()){ // comprime
		crdx[nx++] = (*qx.begin());
		qx.erase(qx.begin());
	}
	
	ny = 0;
	while (!qy.empty()){
		crdy[ny++] = (*qy.begin());
		qy.erase(qy.begin());
	}	

	for (int i = 1; i < nx; i++){
		for (int j = 1; j < ny; j++)
			memo[i][j] = val[{crdx[i], crdy[j]}] + memo[i - 1][j] + memo[i][j - 1] - memo[i - 1][j - 1]; 
	}

	ll ans = 0; // impares

	for (int i = 1; i < nx - 1; i++) // pula 0 não conta n + 1
		for (int j = 1; j < ny - 1; j++){
			if (memo[i][j] % 2)
				ans += (crdx[i + 1] - crdx[i]) * (crdy[j + 1] - crdy[j]);
				// se (crdx[i], crdy[j]) é impar, todas as células no 
				// até as proximas coordenadas também serão.
				// dividimos o trabuleiro em várias partes e checamos todas.
		}

	cout<<ans<<' '<<(n * m - ans)<<endl;		
}

int32_t main(){
	//freopen("dull.in", "r", stdin);
	fastio;
	int T;
	cin>>T;
	while (T--)
		solve();
}