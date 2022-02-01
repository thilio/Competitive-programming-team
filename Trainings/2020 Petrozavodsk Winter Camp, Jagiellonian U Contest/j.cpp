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
const int MAXN = 1e6 + 10; // coordinate dize

int id[MAXN], sz[MAXN];

int find(int a){
	if (id[a] == a) return a;
	return id[a] = find(id[a]);
}

void merge(int a, int b){
	if (a == 0 or b == 0) return;
	a = find(a);
	b = find(b);
	if (a == b) return;
	if (sz[a] < sz[b]) swap(a, b);
	id[b] = a;
	sz[a] += sz[b];	
}


int mx[4] = {1, -1, 0, 0};
int my[4] = {0, 0, 1, -1};

int n, pnt[3];
map<pii, int> paral[3]; // parallel set
vi perp[3][3][MAXN]; // perpendicular set

// 0 = x, 1 = y, 2 = z

void join(int v, vi &a){
	while (a.size() > 1){ // we dont need to keep everyone
		merge(v, a.back());
		a.pop_back();
	}
	if (!a.empty()) // we must conserve at least one to be representant
		merge(v, a.back());
}

int getid(){
	fr(i, 3)
		if (paral[i][{pnt[(i + 1) % 3], pnt[(i + 2) % 3]}] != 0)
			return find(paral[i][{pnt[(i + 1) % 3], pnt[(i + 2) % 3]}]);
	
	assert(0);	
}

void solve(){
	cin>>n;

	fr(i, n + 10){ // init union-find
		id[i] = i;
		sz[i] = 1;
	}

	fr(i, 3){
		paral[i].clear();
		fr(j, 3)
			fr(k, MAXN)
				perp[i][j][k].clear();
	}

	frr(v, n){
		cin>>pnt[0]>>pnt[1]>>pnt[2];

		fr(i, 3)
			if (pnt[i] == -1){
				int x = pnt[(i + 1) % 3];
				int y = pnt[(i + 2) % 3];

				for (int k = 0; k < 4; k++) // merge with parallel holes
					merge(v, paral[i][{x + mx[k], y + my[k]}]);

				for (int dlt = -1; dlt <= 1; dlt++){ // diference in coordinates to join with perpendicular
					join(v, perp[(i + 1) % 3][(i + 2) % 3][y + dlt]);
					join(v, perp[(i + 2) % 3][(i + 1) % 3][x + dlt]);
				}

				paral[i][{x, y}] = v; // parallel to i axis in these coordinates
				perp[i][(i + 1) % 3][x].push_back(v); // perpendicular to (i + 1) % 3 crossing at x
				perp[i][(i + 2) % 3][y].push_back(v);
			}
	}

	int q;
	cin>>q;

	while (q--){
		cin>>pnt[0]>>pnt[1]>>pnt[2];
		int v = getid();

		cin>>pnt[0]>>pnt[1]>>pnt[2];
		int u = getid();
		
		if (u == v)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
}


signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin>>T;
	while (T--)
		solve();
}