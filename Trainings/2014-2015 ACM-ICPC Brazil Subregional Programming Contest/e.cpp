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
const int MAXN = 55;

int mx[4] = {1, -1, 0, 0};
int my[4] = {0, 0, 1, -1};

int n, m, mapa[MAXN][MAXN];

bool valid(int x, int y){
	return x >= 0 and x < n and y >= 0 and y < n;
}

inline int crd(int x, int y){
	return x * n + y;
}

int ans, cnt;	
int vis[MAXN][MAXN];
vii in;

void backtrack(int x, int y, int cst, int mn){
	cst += mapa[x][y]; // entrei na solução
	
	if (in.size() == m - 1){
		ans = max(ans, cst);
	//	dbg(ans);
		return;
	}

	if (cst + (m - 1 -((int) in.size())) * cnt <= ans) // não vou melhorar
		return;

	in.pb({x, y});
	vis[x][y] = 1;

	int ax, ay;
	for (int i = 0; i < in.size(); i++)
		for (int k = 0; k < 4; k++){
			ax = in[i].fst + mx[k];
			ay = in[i].snd + my[k];
			if (valid(ax, ay) and !vis[ax][ay] and crd(ax, ay) >= mn)
				backtrack(ax, ay, cst, mn);
		}

	in.pop_back();	
	vis[x][y] = 0;
}

// Não era para passar,  não passa sem o random_shuffle
// e pode ter que tentar varias vezes.
// A solução esperada é tentar todos os formatos de
// espaço conexo de tamanho m.

int32_t main(){
	std::srand ( unsigned ( std::time(0) ));
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>m;
	
	fr(i, n)
		fr(j, n){
			cin>>mapa[i][j];
			cnt = max(cnt, mapa[i][j]);
		}

	vii ini;	

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ini.pb({i, j});
	random_shuffle(all(ini));	
	random_shuffle(all(ini));	
	random_shuffle(all(ini));	
	random_shuffle(all(ini));	

	for (auto e : ini)
		backtrack(e.fst, e.snd, 0, crd(e.fst, e.snd));

	cout<<ans<<endl;
}