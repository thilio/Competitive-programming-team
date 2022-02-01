#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

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

char mapa[51][51];
int n;

// 3 2 3
// 2 D 2
// 3 2 3
int mx[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int my[8] = {0, 1, 0, -1, -1, 1, 1, -1};

bool valid(int x, int y){
	return !(x < 0 or x >= n or y < 0 or y >= n);
}

int crd(int x, int y){
	return x * n + y;
}

typedef tuple<int, int, int> tup;
vii term;

int dista[MAXN], dist[20][20];

void dij(int src){
	fill(dista, dista + MAXN, -1);
	priority_queue<tup, vector<tup>, greater<tup> > pq;
	pq.push({0, term[src].fst, term[src	].snd});

	int dst, x, y, xx, yy;
	while (!pq.empty()){
		tie(dst, x, y) = pq.top();
		pq.pop();
		
		if (dista[crd(x, y)] != -1)
			continue;
		dista[crd(x, y)] = dst;

		for (int k = 0; k < 8; k++){
			xx = x + mx[k];
			yy = y + my[k]; 
			if (valid(xx, yy) and dista[crd(xx, yy)] == -1)
				pq.push({dst + (k < 4 ? 2 : 3), xx, yy});
		}
	}

	for(int i = 0; i < term.size(); i++)
		dist[src][i] = dista[crd(term[i].fst, term[i].snd)];
}

int memo[1<<20][20];
int nt;
int tsp(int mask, int node){
	if (__builtin_popcount(mask) == 0)
		return dist[node][0];

	int &pdm = memo[mask][node];
	if (pdm != -1)
		return pdm;
	pdm = INF;

	for (int i = 1; i < nt; i++)
		if (mask & (1<<i)){
			int aux = tsp(mask ^ (1<<i), i);
			pdm = min(pdm, aux + dist[node][i]);
		}
	return pdm;	

}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>n;
	while (n != 0){
		term.clear();

		string s;
		fr(i, n){
			cin>>s;
			fr(j, n){
				mapa[i][j] = s[j];
				if (s[j] != '.')
					term.pb({i, j});
			}
		}

		nt = term.size();

		fr(i, nt)
			dij(i);

		memset(memo, -1, sizeof memo);	
		
		// bitset<16> ssd = (1<<nt) - 2;

		// dbg(nt);
	//	cout<<ssd<<endl;

		int ans = tsp((1<<nt) - 2, 0);	

		cout<<ans<<endl;

		cin>>n;
	}

}