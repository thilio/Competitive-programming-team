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
const int MAXN = 3e5 + 10;

ll sum, v[MAXN];

int seg[4 * MAXN];

void update(int node, int l, int r, int ql, int qr, int op){ // 0 para or, 1 para xor
	//cout<<node<<' '<<l<<' '<<r<<' '<<ql<<' '<<qr<<endl;

	if (qr < l or r < ql) // out of bounds
		return;
	if (l == r){
		sum -= v[l];
		if (op == 0)
			v[l] = v[l] | (v[l] - 1);
		else
			v[l] = v[l] ^ (v[l] - 1);
		sum += v[l];	
		seg[node]++;
		return;
	}

	int meio = (l + r) / 2;
	if (op == 0){// or
		if (seg[node<<1] == 0)
			update(node<<1, l, meio, ql, qr, op);
		if (seg[node<<1|1] == 0)
			update(node<<1|1, meio + 1, r, ql, qr, op);
	}
	else{
		if (seg[node<<1] <= 1)
			update(node<<1, l, meio, ql, qr, op);
		if (seg[node<<1|1] <= 1)
			update(node<<1|1, meio + 1, r, ql, qr, op);
	}

	seg[node] = min(seg[node<<1], seg[node<<1|1]);
}



int32_t main(){
	freopen("orxor.in","r",stdin);	
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, q;
	cin>>n>>q;

	frr(i, n){
		cin>>v[i];
		sum += v[i];
	}
	int op, l, r;
	while (q--){
		cin>>op>>l>>r;
		update(1, 1, n, l, r, op - 1);
		cout<<sum<<endl;
	}
}