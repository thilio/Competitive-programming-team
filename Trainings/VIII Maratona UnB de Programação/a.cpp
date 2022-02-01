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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int n;
pii pos[21];

double dist(int a, int b){
	return hypot(pos[a].fst - pos[b].fst, pos[a].snd - pos[b].snd);
}

double memo[21][1<<20];

double tsp(int v, int msk){
	if (__builtin_popcount(msk) == 0)
		return dist(0, v); // volta para origem

	double &pdm = memo[v][msk];
	if (pdm != -1)
		return pdm;

	pdm	= llINF;

	for (int u = 0; u < n; u++)
		if ((1<< u) & msk) // não visitei ainda 
			pdm = min(pdm, tsp(u, msk - (1 << u)) + dist(v, u));
	return pdm;	
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n;

	int x, y;
	fr(i, n){
		cin>>x>>y;
		pos[i] = {x, y};
	}

	fr(i, 21)
		fr(j, 1<<20)
			memo[i][j] = -1;

	cout<<setprecision(9)<<fixed;		
	cout<<tsp(0, (1<<n) - 2)<<endl; // sempre começa no zero
}