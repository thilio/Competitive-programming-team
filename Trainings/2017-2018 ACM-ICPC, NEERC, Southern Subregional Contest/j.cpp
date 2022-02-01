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
const int MAXN = 1e5 + 10;

typedef tuple<ll, ll, ll> tup;

ll seg[4 * MAXN], lazy[4 * MAXN];


void unlazy(ll node, ll l, ll r){ // zera intervalo
	if (lazy[node] == 0) // não faz nada
		return;

	if (l != r){
		lazy[node * 2] = 1;
		lazy[node * 2 + 1] = 1;
	}

	seg[node] = 0;
	lazy[node] = 0;
}


void update_point(ll node, ll l, ll r, ll pos, ll val){
	unlazy(node, l, r);
	
	if (pos < l or r < pos)
		return;

	if (l == r){
		seg[node] += val;
		return;
	}

	ll meio = (l + r)/2;
	update_point(node * 2, l, meio, pos, val);
	update_point(node * 2 + 1, meio + 1, r, pos, val);
	seg[node] = seg[node * 2] + seg[node * 2 + 1];
}


void update_range(ll node, ll l, ll r, ll ul, ll ur){
	unlazy(node, l, r);
	if (ur < l or r < ul)
		return;
	if (ul <= l and r <= ur){
		lazy[node] = 1;
		unlazy(node, l, r);
		return;
	}

	ll meio = (l + r)/2;

	update_range(node * 2, l, meio, ul, ur);
	update_range(node * 2 + 1, meio + 1, r, ul, ur);
	seg[node] = seg[node * 2] + seg[node * 2 + 1];
}

ll query(ll node, ll l, ll r, ll ql, ll qr){
	unlazy(node, l, r);

	if (r < ql or qr < l)
		return 0;
	if (ql <= l and r <= qr)
		return seg[node];

	ll meio = (l + r)/2;

	return query(node * 2, l, meio, ql, qr) + query(node * 2 + 1, meio + 1, r, ql, qr);
}

ll n, m, a[MAXN], b[MAXN], p[MAXN], last[MAXN];
vector<tup> bld;	

bool add(ll id){
	ll l = 0;
	ll r = last[id];
	ll best = -1;

	while (l <= r){
		ll meio = (l + r)/2;
		ll sum = query(1, 0, n - 1, meio, last[id]);

		if (sum >= p[id]){ // posso pagar
			best = meio;
			l = meio + 1;
		}
		else{ // tenho que ir mais longe
			r = meio - 1;
		}
	}

	if (best == -1) // não consigo pagar essa demolição
		return false;

	// tenho que zerar o intervalo (best, last[id]] e deduzir o saldo remanescente do best

	if (best == last[id]) // só deduzo nesse dia
		update_point(1, 0, n - 1, last[id], -p[id]);
	else{
		ll sum = query(1, 0, n - 1, best + 1, last[id]);
		update_range(1, 0, n - 1, best + 1, last[id]); // zero essas posições
		update_point(1, 0, n - 1, best, -(p[id] - sum)); // deduzo o restante dessa
	}

	return true;
}





int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>n>>m;
	
	fr(i, n)
		cin>>a[i];

	fr(i, m)
		cin>>b[i];	
	fr(i, m)
		cin>>p[i];
	fr(i, m)
		bld.pb({b[i], p[i], i});

	sort(all(bld));		

	int pp = 0;
	for (ll i = n - 1; i >= 0; i--){
		while (pp < m and get<0>(bld[pp]) <= a[i]){ // ultimo dia que posso ir
			last[get<2>(bld[pp])] = i;
			pp++;
		}
	}

	while (pp < m){ // não pode ser demolido nenhum dia
		bld.pop_back();
		m--;
	}

	for (int i = 0; i < m; i++){
		int ab, ap, aid;
		tie(ab, ap, aid) = bld[i];
		bld[i] = {ap, ab, aid};
	}

	sort(all(bld)); // ordena por custo agora

	for (int i = 0; i < n; i++) // adiciona custos na seg
		update_point(1, 0, n - 1, i, a[i]);

	ll ans = 0;
	for (int i = 0; i < m; i++) // tento adicionar o i-ésimo mais barato
		ans += add(get<2>(bld[i]));

	cout<<ans<<endl;
}