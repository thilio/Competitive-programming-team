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
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 4e3 + 10;

typedef tuple<int, int, int> tup;

int n;
vector<tup> pshow[11], show[MAXN];
int memo[MAXN][MAXN];
int mxt;
int pd(int mask, int tme){
	if (tme >= mxt){
		if (__builtin_popcount(mask) == n)
			return 0;
		else
			return -INF;
	}

	int &pdm = memo[mask][tme];
	if (pdm != -1)
		return pdm;

	pdm = pd(mask, tme + 1);

	int fim, stg, cst;
	for (auto x : show[tme]){
		tie(fim, stg, cst) = x; // tempo, stage, custo
		pdm = max(pdm, pd( (mask | (1<<stg)) , fim) + cst);
	}

	if (pdm < 0) // deu errado ou não pegou ninguem
		pdm = -INF;
	return pdm;		
}

set<int> val;
map<int, int> cmp;

int32_t main(){
	fastio;
	cin>>n;

	int a, b, c, m;
	fr(i, n){
		cin>>m;
		fr(j, m){
			cin>>a>>b>>c;
			val.insert(a);
			val.insert(b);
			pshow[i].pb({a, b, c}); // ini, fim, custo
		}
	}

	while (!val.empty()){
		cmp[*val.begin()] = mxt++;
		val.erase(val.begin());
	}

	fr(i, n){
		for (auto &x : pshow[i]){
			tie(a, b, c) = x;
			show[cmp[a]].pb({cmp[b], i, c});//show por tempo
		}
	}

	fr(i, MAXN)
		fr(j, MAXN)
			memo[i][j] = -1;

	int ans = pd(0, 0);

	if (ans <= 0)
		cout<<-1<<endl;
	else
		cout<<ans<<endl;
}