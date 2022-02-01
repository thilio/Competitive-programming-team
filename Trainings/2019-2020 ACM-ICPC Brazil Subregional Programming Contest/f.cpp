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
const int MAXN = 2e5 + 10;

#define int ll

typedef tuple<int, int, int, int> tup4;

int n, bx, by, tx, ty, P; // top right
vector<tup4> river, event;

int lazy[4 * MAXN];
pair<ll, ll> seg[4 * MAXN];

pair<ll, ll> combine(pii b, pii c){
	pii ans;
	if (b.fst == c.fst){
		ans = b;
		ans.snd += c.snd;
	}
	else{
		if (b.fst < c.fst)
			ans = b;
		else
			ans = c;
	}
	return ans;
}

void unlazy(int node, int l, int r){
	if (l != r){
		lazy[node<<1] += lazy[node];
		lazy[node<<1|1] += lazy[node];
	}
	seg[node].fst += lazy[node];
	lazy[node] = 0;
}

void build(int node, int l, int r){
	if (l == r){
		seg[node] = {0, 1};
		return;
	}

	int meio = (l + r)/2;

	build(node<<1, l, meio);
	build(node<<1|1, meio + 1, r);
	seg[node] = combine(seg[node<<1], seg[node<<1|1]);
}

void modfy(int node, int l, int r, int ql, int qr, int val){
	unlazy(node, l, r);
	if (r < ql or qr < l)
		return;
	if (ql <= l and r <= qr){
		lazy[node] = val;
		unlazy(node, l, r);
		return;
	}

	int meio = (l + r)/2;

	modfy(node<<1, l, meio, ql, qr, val);
	modfy(node<<1|1, meio + 1, r, ql, qr, val);
	seg[node] = combine(seg[node<<1], seg[node<<1|1]);
}

pair<ll, ll> query(int node, int l, int r, int ql, int qr){
	unlazy(node, l, r);
	if (r < ql or qr < l)
		return {INF, 0};
	
	if (ql <= l and r <= qr)
		return seg[node];
	
	int meio = (l + r)/2;

	return combine(	query(node<<1, l, meio, ql, qr), 
		query(node<<1|1, meio + 1, r, ql, qr));
}

// gera os eventos
void generate(int r){
	event.clear();

	int x1, y1, x2, y2;

	for (int i = 0; i < river.size(); i++){
		tie(x1, y1, x2, y2) = river[i];

		x1 -= r, y1 -= r;
		x2 += r, y2 += r;

		x1 = max(x1, bx);
		y1 = max(y1, by);
		x2 = min(x2, tx);
		y2 = min(y2, ty);

		event.pb({x1, 0, y1, y2}); // entra
		event.pb({x2, 1, y1, y2}); // sai
	} 

	sort(all(event));
}

bool test(int r){
	generate(r);

	build(1, 1, MAXN);
	memset(lazy, 0, sizeof lazy);

	ll ans = 0, x, typ, y1, y2;
	ll lst = bx, dy, p, ttyp, xx;

	pii qry;
	p = 0;
	while (p < (int)event.size()){
		tie(x, typ, y1, y2) = event[p];
		
		xx = x;
		ttyp = typ;

		dy = MAXN - seg[1].snd;

		ans += (x - lst) * dy;
		lst = x;

		if (p == ((int)event.size()) - 1) // acabou
			break;

		while (x == xx and ttyp == 0){ //adiciona
			modfy(1, 1, MAXN, y1 + 1, y2, 1);
			tie(xx, ttyp, y1, y2) = event[++p]; // ok, so acaba quando sai	
		}

		if (xx != x)
			continue;

		while (x == xx and ttyp == 1){ //remove
			modfy(1, 1, MAXN, y1 + 1, y2, -1);
			if (p < ((int)event.size()) - 1)
				tie(xx, ttyp, y1, y2) = event[++p];
			else 
				break;
		}
	}


	ll at = (tx - bx) * (ty - by);
	return 100ll * ans >= P * at;
}
 
int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n;
 
	int x1, y1, x2, y2;
	fr(i, n){
		cin>>x1>>y1>>x2>>y2;
		if (y1 == y2){ // horizontal
			if (x1 > x2)
				swap(x1, x2);
		}	
		else{
			if (y1 > y2)
				swap(y1, y2);
		}
		river.pb({x1, y1, x2, y2});
	}
 
	cin>>P;
	cin>>bx>>by>>tx>>ty;

	for (auto &e : river){ // tomo mundo ta a partir do zero agora
		tie(x1, y1, x2, y2) = e;
		x1 -= bx;
		x2 -= bx;
		y1 -= by;
		y2 -= by;

		e = {x1, y1, x2, y2};
	}

	tx -= bx;
	ty -= by;
	bx = by = 0;

	int ini, fim, meio, bst;
	ini = 1;
	fim = bst = 1e5 + 10;
 
	while (ini <= fim){
		meio = (ini + fim)/2;
		
		if (test(meio)){
			fim = meio - 1;
			bst = meio;
		}
		else
			ini = meio + 1;
	}
 
	cout<<bst<<endl;
}