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
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 2e6 + 10;

struct segtree{
	int seg[4 * MAXN];

	// segtree(){};

	void init (int n){
		for (int i = 0; i < 4 * n + 10; i++)
			seg[i] = 0;
	}

	void update(int node, int l, int r, int pos){
		if (r < pos or pos < l)
			return;
		if (l == r){
			seg[node]++;
			return;
		}

		int meio = (l + r)/2;

		update(node<<1, l, meio, pos );
		update(node<<1|1, meio + 1, r, pos);

		seg[node] = seg[node<<1] + seg[node<<1|1];
	}

	int query(int node, int l, int r, int ql, int qr){
		if (qr < l or r < ql)
			return 0;
		if (ql <= l and r <= qr)
			return seg[node];
		int meio = (l + r)/2;

		return query(node<<1, l, meio, ql, qr) + query(node<<1|1, meio + 1, r, ql, qr);
	}
};

segtree ini[2], fim[2];

// 1 moscow, 2 denver

int n, m, q, cnt, op[MAXN];
pii v1[MAXN], v2[MAXN], v3[MAXN];

map<int, int> crd;

void solve(){
	cin>>n;
	fr(i, n)
		cin>>v1[i].fst>>v1[i].snd;

	cin>>m;	
	fr(i, m)
		cin>>v2[i].fst>>v2[i].snd;

	cin>>q;
	fr(i, q)
		cin>>op[i]>>v3[i].fst>>v3[i].snd;

	crd.clear();
	set<int> comp;

	fr(i, n){
		comp.insert(v1[i].fst);
		comp.insert(v1[i].snd);	
	}
	
	fr(i, m){
		comp.insert(v2[i].fst);
		comp.insert(v2[i].snd);	
	}

	fr(i, q){
		comp.insert(v3[i].fst);
		comp.insert(v3[i].snd);	
	}

	cnt = 2;
	while (!comp.empty()){
		crd[*comp.begin()] = cnt++;
		comp.erase(comp.begin());
	}	

	fr(i, n)
		v1[i] = {crd[v1[i].fst], crd[v1[i].snd]};
	fr(i, m)
		v2[i] = {crd[v2[i].fst], crd[v2[i].snd]};
	fr(i, q)
		v3[i] = {crd[v3[i].fst], crd[v3[i].snd]};

	fr(i, 2){
		ini[i].init(cnt + 1);	
		fim[i].init(cnt + 1);	
	}
	
	fr(i, n){
		ini[0].update(1, 1, cnt, v1[i].fst);
		fim[0].update(1, 1, cnt, v1[i].snd);
	}

	ll ans = ((ll) n) * ((ll) m);

	fr(i, m){
		ini[1].update(1, 1, cnt, v2[i].fst);
		fim[1].update(1, 1, cnt, v2[i].snd);	
		
		ll nsec = fim[0].query(1, 1, cnt, 1, v2[i].fst - 1); // termina antes do meu começo
		nsec += ini[0].query(1, 1, cnt, v2[i].snd + 1, cnt); // termina antes do meu começo

		ans -= nsec;
	}

	cout<<ans<<endl;

	int l, r, c;
	fr(i, q){
		tie(l, r) = v3[i];
		if (op[i] == 1){ // vou botar na primeira seg
			ll nsec = m;
			
			nsec -= fim[1].query(1, 1, cnt, 1, l - 1); // termina antes do meu começo
			nsec -= ini[1].query(1, 1, cnt, r + 1, cnt); 

			ans += nsec;
			n++;
		}
		else{
			ll nsec = n;
			
			nsec -= fim[0].query(1, 1, cnt, 1, l - 1); // termina antes do meu começo
			nsec -= ini[0].query(1, 1, cnt, r + 1, cnt); 

			ans += nsec;

			m++;
		}

		ini[op[i] - 1].update(1, 1, cnt, l);
		fim[op[i] - 1].update(1, 1, cnt, r);
		cout<<ans<<endl;
	}

}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin>>T;

	frr(i, T){
		cout<<"Case "<<i<<": ";
		solve();
	}
}