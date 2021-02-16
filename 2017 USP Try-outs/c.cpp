#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define frm(i, n) for(int i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 500010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

int n, m, r;
int a[MAXN];
vector<pii> Div[MAXN]; /*Div[i] são os Divisores de a[i]*/

int remMulti(int x){
	int X = x;
	vector<pii> d;
	d.pb({1, 0});
	int p = 2;
	int ret = 1;
	vector<pii> aux;
			
	for(int i = 2; i*i <= x; i++){
		if(x%i == 0){
			ret *= i;
			while(x%i == 0) x /= i;
			aux.clear();
			for(auto y: d) aux.pb({i*y.f, y.s+1});
			for(auto y: aux) d.pb(y);
		}
	}

	if(x > 1){
		ret *= x;
		aux.clear();
		for(auto y: d) aux.pb({x*y.f, y.s+1});
		for(auto y: aux) d.pb(y);
	}

	Div[ret] = d;

	return ret;
}

void read(){
	cin >> n >> m;
	frr(i, n){
		cin >> a[i];
		a[i] = remMulti(a[i]);
	}
}

/*
	l[x] são os índices i tais que x | a[i]
*/
vector<int> l[MAXN];

/*
	retorna a quantidade de a's com índice entre [i, j) que são múltiplos de x
*/
int mult(int x, int i, int j){
	int ret = (lower_bound(l[x].begin(), l[x].end(), i) - l[x].begin()); 
	//cout << x << " " << i << ' ' << j << " " << l[x].size() << endl;
	return l[x].size() - ret;
}

/*
	Retorna a quantidade de a's com índice entre [i, j) que não são coprimos com a[j]
*/
int ncop(int i, int j){
	int ans = 0;
	for(auto par : Div[a[j]]){
		if(par.f == 1) continue;
		if(par.s%2 == 1) ans += mult(par.f, i, j);
		else ans -= mult(par.f, i, j);
	}
	return ans;
}

int findPr(int j){
	int lo = 0, hi = j, m;

	while(lo < hi - 1){
		m = (lo + hi)/2;

		//cout << ncop(m, j) <<" | " << m << " " << j << endl;

		if(ncop(m, j) == j - m){
			//cout << lo << " | " << m << " " << j << endl;
			hi = m;
		}
		else lo = m;
	}

	for(auto d : Div[a[j]]) {
		l[d.f].pb(j);
	}

	return lo;
}

class SEG{
private:
	vector<int> v;
	int node[MAXN];
	int n;
	void build(int i, int l, int r){
		if(l == r) {
			node[i] = v[l];
		}
		else{
			int m = (l + r)/2;
			build(2*i, l, m);
			build(2*i + 1, m + 1, r);
			node[i] = max(node[2*i], node[2*i+1]);
		}
	}
public:
	SEG(vector<int> & davez){
		v = davez;
		n = davez.size() - 1;
		build(1, 1, n);
	}

	int query(int i, int l, int r, int ql, int qr){
		if(ql > r || l > qr) return -1;
		else if(ql <= l && r <= qr) return node[i];
		else{
			int m = (l + r)/2;
			return max(query(2*i, l, m, ql, qr), query(2*i + 1, m + 1, r, ql, qr));
		}
	}
};

int main(){
	fastio;
	read();
	
	vector<int> pr(n+1);
	frr(i, n){
		pr[i] = findPr(i);
		//cout << pr[i] << " ";
	}
	//cout << endl;

	SEG s(pr);
	while(m--){
		int l, r;
		cin >> l >> r;
		if(s.query(1, 1, n, l, r) >= l) {
			cout << "S\n";
		}
		else cout << "N\n";
	}
}
