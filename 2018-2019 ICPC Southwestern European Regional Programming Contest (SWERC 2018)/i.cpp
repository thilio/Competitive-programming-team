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
const int MAXN = 1e3 + 10;

int mx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int my[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

int n, m;
bool mapa[MAXN][MAXN], vis[MAXN][MAXN];

bool valid(int x, int y){
	return (x >= 0 and x < n) and (y >= 0 and y < m);
}

int esq, dir, cim, bix;

void update_corner(int x, int y){
	if (esq == -1) esq = y;
	else esq = min(esq, y);

	dir = max(dir, y);

	if (cim == -1) cim = x;
	else cim = min(x, cim);

	bix = max(bix, x);
}


void dfs(int x, int y){
	vis[x][y] = 1;

	update_corner(x, y);

	for (int k = 0; k < 8; k++){
		int xn = x + mx[k];
		int yn = y + my[k];
		if (valid(xn, yn) and !vis[xn][yn] and mapa[xn][yn])
			dfs(xn, yn); 
	}
}

void fill(int x, int y){
	esq = dir = cim = bix = -1;
	dfs(x, y);
}

int sum[MAXN][MAXN];

int getsum(int a, int b, int c, int d){ // inferior direito (c, d) até superior esquerdo (a, b) em relação ao zero
	return sum[c][d] + sum[a - 1][b - 1] - sum[a - 1][d] - sum[c][b - 1];
}


int test(int px, int py){
	fill(px, py);

	if (esq == dir) return 0;

	int l = dir - esq + 1; // 2x + y = l
	int h = bix - cim + 1;// 3x + 2y = h

	int x = 2 * l - h;
	int y = 2 * h - 3 * l;

	if (x <= 0 or y <= 0) return 0;

	// testar as letras
	int tot = getsum(cim, esq, bix, dir); // cima é a parte de cima da letra (menor coord)
	                                     // baixo é a parte de baixo (maior coord)
  // A
	if (l * h == y * y + (x + y) * y + tot) // bate pontos pretos
			return 1;
	
	if (l * h == tot + 2 * y * y)
			return 2; 

	if (l * h == (x + y) * (2 * y + x) + tot)
			return 3;

	return 0;
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>m>>n;

	string s;
	fr(i, n){
		cin>>s;
		fr(j, m)
			mapa[i][j] = (s[j] == '#');
	}

	for (int i = 1; i < n - 1; i++) // tirar ruido
		for (int j = 1; j < m - 1; j++){ // nao passo pelas bordas
			if (!mapa[i][j])
				continue;

			bool ok = 0;
			for (int k = 0; k < 8; k++){
				int x = i + mx[k];
				int y = j + my[k];
				ok |= mapa[x][y];
			}

			if (!ok)
				mapa[i][j] = 0;
		}	


	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++){
			sum[i][j] = mapa[i][j];

			if (i > 0)
				sum[i][j] += sum[i - 1][j];
			if (j > 0)
				sum[i][j] += sum[i][j - 1];
			if (i > 0 and j > 0)
				sum[i][j] -= sum[i - 1][j - 1];
		}


	fill(0, 0); // pinta a borda

	int A, B, C;


	A = B = C = 0;

	for (int i = 1; i < n - 1; i++)
		for (int j = 1; j < m - 1; j++){
			if (mapa[i][j] and !vis[i][j]){
				int res = test(i, j);

     			if (res == 1)
					A++;
				else if (res == 2)
					B++;
				else if (res == 3)
					C++;
			}
		} 		

	cout<<A<<' '<<B<<' '<<C<<endl;
}