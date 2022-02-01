#include "bits/stdc++.h"
using namespace std;

#define endl '\n'

#define all(x)  x.begin(),x.end()

const int MAXN = 5e5 + 10;
const int LMAXN = 25;

int n, q;
int memo[MAXN][LMAXN];

vector<int> v;
vector<int> tree[4 * MAXN];

void build(int node, int l, int r){
	if (l == r) return tree[node].push_back(v[l]);
	int meio = (l + r)/2;
	build(node<<1, l, meio); 
	build(node<<1|1, meio + 1, r);
	merge(all(tree[node<<1]), all(tree[node<<1|1]), back_inserter(tree[node]));
}

int query(int node, int l, int r, int ql, int qr, int val){
	if (qr < l or r < ql) return 0;
	if (ql <= l and r <= qr)
		return lower_bound(all(tree[node]), val + 1) - tree[node].begin();
	int meio = (l + r)/2;
	return query(node<<1, l, meio, ql, qr, val) + query(node<<1|1, meio + 1, r, ql, qr, val);
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>q;

	v.push_back(0);
	for (int i = 1; i <= n; i++){
		cin>>memo[i][0];
		v.push_back(min(i, memo[i][0]));
	}

	for (int k = 1; k < LMAXN; k++){
		for (int i = 1; i <= n; i++){
			memo[i][k] = memo[memo[i][k - 1]][k - 1];
			v[i] = min(v[i], v[memo[i][k]]);	
		}
	}

	build(1, 1, n);
	int l, r, ini, fim, meio, best, bval;

	while (q--){
		cin>>l>>r;

		ini = 1; 
		fim = best = n;
		bval = r - l + 1;

		while (ini <= fim){
			meio = (ini + fim)/2;
			int aux = query(1, 1, n, l, r, meio); // números <= meio
			int aux2 = (r - l + 1) - aux; // números > meio

			if (abs(aux - aux2) < bval){
				bval = abs(aux - aux2);
				best = meio;
			}

			if (aux >= (r - l + 1)/2) // mais da metade para baixo
				fim = meio - 1;
			else
				ini = meio + 1;
		}

		ini = 1;
		fim = best;

		while (ini <= fim){ // acha o cara mais a esquerda
			meio = (ini + fim)/2;
			int aux = query(1, 1, n, l, r, meio); // números <= meio
			int aux2 = (r - l + 1) - aux;
			
			if (abs(aux - aux2) == bval){
				best = min(best, meio);
				fim = meio - 1;
			}
			else
				ini = meio + 1;
		}

		cout<<best<<endl;
	}
}