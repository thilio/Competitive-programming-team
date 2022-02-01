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
const int MAXN = 2e5 + 10;

int n, m, c[MAXN];
ll  v[MAXN];

int pre[MAXN];
set<int> pos[MAXN];

ll segval[4 * MAXN], segmax[4 * MAXN];

void update(int node, int l, int r, int pos){
	if (pos < l or r < pos) return;	

	if (l == r){
		segval[node] = v[pos];
		segmax[node] = pre[pos];
		return;
	}
	int m = (l + r)/2;

	update(node<<1, l, m, pos);
	update(node<<1|1, m + 1, r, pos);

	segval[node] = segval[node<<1] + segval[node<<1|1];
	segmax[node] = max(segmax[node<<1], segmax[node<<1|1]);
}

ll query_val(int node, int l, int r, int ql, int qr){
	if (qr < l or r < ql) 
		return 0;

	if (ql <= l and r <= qr)	
		return segval[node];

	int m = (l + r)/2;
	return query_val(node<<1, l, m, ql, qr) + query_val(node<<1|1, m + 1, r, ql, qr);
}

int query_max(int node, int l, int r, int ql, int qr, int lim){
	if (qr < l or r < ql) 
		return 0;

	if (segmax[node] < lim)
		return 0;

	if (l == r)
		return segmax[node];

	int m = (l + r)/2;
	int aux = query_max(node<<1, l, m, ql, qr, lim);
	if (aux >= lim)
		return aux;
	return query_max(node<<1|1, m + 1, r, ql, qr, lim);
}

void change(int x, int y, int z){

	auto p = pos[c[x]].lower_bound(x + 1);
	if (p != pos[c[x]].end()){
		int k = *p;
		pre[k] = pre[x];
		update(1, 1, n, k);
	}

	pos[c[x]].erase(x);

	p = pos[y].lower_bound(x);
	if (p != pos[y].end()){
		int k = *p;
		pre[x] = pre[k];
		pre[k] = x;

		update(1, 1, n, k);
	}
	else{
		pre[x] = 0;
		if (!pos[y].empty())
			pre[x] = *pos[y].rbegin();
	}

	c[x] = y;
	v[x] = z;
	pos[y].insert(x);

	update(1, 1, n, x);
}

ll used[MAXN];

ll ask(int s, int k){

	ll sum = 0;
	int p = s;
	stack<int> stk;

	for (int r = 0; r < k + 1; r++){
		int nxt = query_max(1, 1, n, p, n, s); // partindo de p, até n, limite s;

		if (nxt < s){// não achou repretição
			sum += query_val(1, 1, n, p, n);
			break;
		}	
		
		nxt = *pos[c[nxt]].lower_bound(nxt + 1); // posição do que repete
		stk.push(c[nxt]);	

		if (r == k){ // não pode mais repetir
			sum += (p < nxt? query_val(1, 1, n, p, nxt - 1) : 0);
			break;
		}	

		// ainda posso repetir
		sum += query_val(1, 1, n, p, nxt); // coloca o cara repetido
		if (used[c[nxt]] == 0){
			used[c[nxt]] = max(v[nxt], v[pre[nxt]]);
			sum -= min<ll>(v[nxt], v[pre[nxt]]);
		}
		else{
			sum -= min<ll>(v[nxt], used[c[nxt]]);
			used[c[nxt]] = max<ll>(used[c[nxt]], v[nxt]);
		}
		p = nxt + 1;
	}

	while (!stk.empty()){
		used[stk.top()] = 0;
		stk.pop();
	}

	return sum;
}

int last[MAXN];
signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n>>m;

	frr(i, n)
		cin>>c[i]>>v[i];

	frr(i, n){
		pre[i] = last[c[i]];	

		pos[c[i]].insert(i);
	
		last[c[i]] = i;
	}


	frr(i, n)
		update(1, 1, n, i);

	int typ, f, g, h;	
	while (m--){
		cin>>typ;

		if (typ == 1){
			cin>>f>>g>>h;
			change(f, g, h);
		}
		else{
			cin>>f>>g;
			cout<<ask(f, g)<<endl;
		}
	}	
}