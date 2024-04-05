/*
   Title: Knuth DP optimization
   Description: Solves the problem of the best order of slipting a array in n given points
   Complexity: O(n**2)
   Details: (In Portuguese)

   Recorrência : pd(i, j) = min_{i < k < j} {pd(i, k) + pd(k, j)} + c[i][j], O(n^3)
    Podemos otimizar se vale que A[i][j - 1]<=A[i][j] <= A[i + 1][j], em que A[i][j] 
    é o ponto de divisão ótimo (o k da recorrência) para o intervalo v[1...j].
    Outra condição : C[a][c]+C[b][d]<=C[a][d]+C[b][c], a<=b<=c<=d.
                     C[b][c] <= C[a][d]    
    Problema, descobrir a ordem otima de particinar uma string em m pontos dados 
    tal que o custo de particionar no ponto i é o tamanho do intervalo
*/

const int MAXN = 1e3 + 10;
const int INF = 0x3f3f3f3f;

int n, m, cuts[MAXN];
int memo[MAXN][MAXN], mid[MAXN][MAXN];

int pd(){
	for (int sz = 0; sz <= m; sz++){ // tamanho do intervalo
		for (int l = 0; l <= m - sz; l++){
			int r = l + sz;
			if (sz < 2){
				memo[l][r] = 0;
				mid[l][r] = l;
				continue;
			}
			int midl = mid[l][r - 1];
			int midr = mid[l + 1][r];
			memo[l][r] = INF;
			mid[l][r] = l;
			for (int k = midl; k <= midr; k++){ // tenta todas as divisões
				int aux = memo[l][k] + memo[k][r] + cuts[r] - cuts[l];
				if (memo[l][r] > aux){
					memo[l][r] = aux;
					mid[l][r] = k;
				}
			}
		}
	}
	return memo[0][m];
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	while (cin>>n>>m){
		frr(i, m)
			cin>>cuts[i];

		cuts[m + 1] = n;
		m++;
		cout<<pd()<<endl;
	}
}