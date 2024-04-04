/*
   Title: Divide and conquer DP optimization
   Description: Divides n elements in m non-empty groups
   Complexity: O(nmlog(n))
   Details: (In Portuguese)
   
   Recorrência : pd(m, n) = min_{1 <= k < n} {pd(m - 1, k) + c[k + 1][n]}, O(nm^2)
   
   Podemos otimizar se vale que A[i][j]<=A[i][j+1], em que A[i][j] é o ponto
   de divisão ótimo (o k da recorrência) para o intervalo v[1...j] com i grupos.
   O ponto de divisão para i é monotono crescente no tamanho do vetor, isto é, 
   para um intervalo maior, nao vale a pena interromper o ultimo grupo antes.
   Outra condição : C[a][d]+C[b][c]>=C[a][c]+C[b][d], a<b<c<d.

   Problema, juntar n elementos em k pilhas de elementos contínuos
   tal que a soma do produto dos pesos com distâncias percorridas é mínima 
   
   Solves: https://vjudge.net/problem/SPOJ-NKLEAVES
*/

const int MAXN = 1e5 + 10;

ll n, m, u[MAXN]; 
ll sum[MAXN], acum[MAXN];
ll dp_before[MAXN], dp_cur[MAXN];
 
// O ponto de divisão ótimo para l <= j <= r está entre [optl, optr] 
void compute(ll l, ll r, ll optl, ll optr){// otimizada O(nmlong(m))
    if (l > r) return;
 
    ll mid = (l + r) >> 1;
 
	ll vmid = llINF, opt = optl;
    for (ll k = optl; k <= min(mid, optr); k++){
    	if (vmid > dp_before[k] + sum[mid] - sum[k] - (acum[mid] - acum[k]) * k){
    		vmid = dp_before[k] + sum[mid] - sum[k] - (acum[mid] - acum[k]) * k;
    		opt = k;
    	}
    }
 
    dp_cur[mid] = vmid;
 
    compute(l, mid - 1, optl, opt); // A[m][mid - 1] <= A[m][mid]
    compute(mid + 1, r, opt, optr); // A[m][mid] <= A[m][r]
}
 
ll pd(){
	for (int i = 1; i <= n; i++) // resolve para 1 grupo
		dp_cur[i] = sum[i];
	dp_cur[0] = llINF;
	
	for (ll i = 1; i < m; i++){ // percorre todas as quantidades de grupos
		memcpy(dp_before, dp_cur, sizeof dp_cur); // copia o estado anterior com i grupos
		compute(1, n, 1, n); // resolve o poblma para i + 1 grupos 
	}
 
	return dp_cur[n];
}
 
int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>m;	
	for (int i = 1; i <= n; i++)
		cin>>u[i];	
 
	sum[1] = 0;
	acum[1] = u[1];
	for (ll i = 2; i <= n; i++){ 
		sum[i] = sum[i - 1] + (i - 1ll) * u[i]; // custo de levar até o 1
		acum[i] = acum[i - 1] + u[i]; // soma acumulada dos pesos
	}
 
	cout<<pd()<<endl;
}