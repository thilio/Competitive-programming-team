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
const ll llINF = (long long)(3e18) + 100;   
const int MAXN = 6e3 + 10;

ll n, b, c, h[MAXN], ans[MAXN], cost[MAXN][MAXN];
ll dp_before[MAXN], dp_cur[MAXN];
 
// O ponto de divisão ótimo para l <= j <= r está entre [optl, optr] 
void compute(ll l, ll r, ll optl, ll optr){// otimizada O(nmlong(m))
    if (l > r) return;
 
    ll mid = (l + r) >> 1;
 
	ll vmid = llINF, opt = optl;
    for (ll k = optl; k <= min(mid, optr); k++){
    	if (vmid > dp_before[k - 1] + cost[k][mid]){
    		vmid = dp_before[k - 1] + cost[k][mid];
    		opt = k;
    	}
    }
 
    dp_cur[mid] = vmid;

    compute(l, mid - 1, optl, opt); // A[m][mid - 1] <= A[m][mid]
    compute(mid + 1, r, opt, optr); // A[m][mid] <= A[m][r]
}
 
void pd(){
	for (int i = 1; i <= n; i++) // resolve para 1 grupo
		dp_cur[i] = cost[1][i];
	dp_cur[0] = llINF;

	ans[1] = cost[1][n];
	
	for (ll i = 1; i < n; i++){ // percorre todas as quantidades de grupos
		memcpy(dp_before, dp_cur, sizeof dp_cur); // copia o estado anterior com i grupos
		compute(1, n, 1, n); // resolve o poblma para i + 1 grupos 
		
		ans[i + 1] = dp_cur[n];
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>b>>c;

	frr(i, n)
		cin>>h[i];

	// precomputar
	for (ll l = 1; l <= n; l++){
		cost[l][l] = b;

		ll mid = l, esq, dir, costr, costl;
		esq = dir = costl = costr = 0;

		for (ll r = l + 1; r <= n; r++){
			dir += h[r];
			costr += (r - mid) * h[r];

			// costl + costr > costl + costr + esq + h[mid] - dir 
			while (mid < r and esq + h[mid] - dir <= 0){
				esq += h[mid];
				costl += esq;

				mid++;

				costr -= dir;
				dir -= h[mid];
			}

			cost[l][r] = (costl + costr) * c + b;
		}
	}	

	pd();

	frr(i, n - 1)
		cout<<ans[i]<<' ';
	cout<<ans[n]<<endl;
}