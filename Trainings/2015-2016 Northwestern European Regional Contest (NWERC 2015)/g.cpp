#include "bits/stdc++.h"
using namespace std;

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

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
const int MAXN = 2e5 + 10;



typedef tree<int,null_type,less<int>,rb_tree_tag, tree_order_statistics_node_update> ordered_set;
// Comandos
// find_by_order(i) -> iterador para o i-ésimo elemento (contando do zero)
// order_of_key(k) -> número de elementos estritamente menores que k
// pode-se subtrair iteradores como em um vector

typedef tuple<int, int, int> tup;

ordered_set seg[4 * MAXN];

void modify(int node, int l, int r, int pos, int val){
	if (pos < l or r < pos)
		return;
	if (l == r){
		seg[node].insert(val);
		return;
	}

	int meio = (l + r)/2;

	modify(node<<1, l, meio, pos, val);
	modify(node<<1|1, meio + 1, r, pos, val);

	// se estou aqui, contenho o intervalo
	seg[node].insert(val);
}

ll query(int node, int l, int r, int ql, int qr, int val){
	if (qr < l or r < ql) 
		return 0;
	if (ql <= l and r <= qr) 
		return seg[node].order_of_key(val);
	int meio = (l + r)/2;
	return query(node<<1, l, meio, ql, qr, val) + query(node<<1|1, meio + 1, r, ql, qr, val);
}

int n, in[MAXN];
tup v[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n;

	int x;
	frr(i, n){
		cin>>x;
		get<0>(v[x - 1]) = i;
	}

	frr(i, n){
		cin>>x;
		get<1>(v[x - 1]) = i;
	}

	frr(i, n){
		cin>>x;
		get<2>(v[x - 1]) = i;
	}

	sort(v, v + n); // ordenado pelo primeiro

	int a, b, c;
	ll ans = 0;
	for (int i = 0; i < n; i++){
		tie(a, b, c) = v[i];

		ans += query(1, 1, n, 1, b, c);
		modify(1, 1, n, b, c);
	}

	cout<<ans<<endl;
}