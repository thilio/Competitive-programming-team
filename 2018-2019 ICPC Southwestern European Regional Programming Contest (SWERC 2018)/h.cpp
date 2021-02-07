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

#define MAXN 300010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

vector<int> caras[MAXN];
int ans = 0, n, e, tot;
int d[3][MAXN];
int nd[4*MAXN];
void build(int i, int l, int r){
	if(l == r) nd[i] = MOD;
	else{
		int m = (l + r)/2;
		build(2*i, l, m);
		build(2*i + 1, m + 1, r);
		nd[i] = min(nd[2*i], nd[2*i + 1]);
	}
}

void update(int i, int l, int r, int pos, int val){
	if(l == r) nd[i] = min(nd[i], val);
	else{
		int m = (l + r)/2;
		if(pos <= m)update(2*i, l, m, pos, val);
		else update(2*i + 1, m + 1, r, pos, val);
		nd[i] = min(nd[2*i], nd[2*i + 1]);
	}
}

int query(int i, int l, int r, int ql, int qr){
	if(l > qr || ql > r) return MOD;
	else if(ql <= l && r <= qr) return nd[i];
	else{
		int m = (l + r)/2;
		return min(query(2*i, l, m, ql, qr), query(2*i + 1, m + 1, r, ql, qr));
	}
} 

void solve(int pos){
	vector<pii> davez;
	for(auto x : caras[pos]){
		if(d[2][x] < query(1, 1, tot, 1, d[1][x]))
			davez.pb({d[1][x], d[2][x]});
		else ans++;
//		cout<< x<< " " << d[1][x] << " " << query(1, 1, tot, 1, d[1][x]) << " | ";
	}
//	cout << endl;	
	
	sort(davez.begin(), davez.end());


	pq<pii, vector<pii>, greater<pii>> fila;

	for(auto x : davez) {
		if(fila.size() == 0) fila.push({x.s, x.f});
		else if(fila.top().f < x.s) {
			ans++;
			continue;
		}
		else if(fila.top().f > x.s) fila.push({x.s, x.f});
		else{
			if(fila.top().s < x.f) ans++;
		}
	}
	while(fila.size()){
		update(1, 1, tot, fila.top().s, fila.top().f);
//		cout << query(1, 1, tot, 1, fila.top().s) << " seg " << fila.top().f<< endl;
		fila.pop();
	}
}

void coordinateCompress(){
	tot = 1;
	set<int> s;
	fr(i, n){
		s.insert(d[0][i]);
		s.insert(d[1][i]);
		s.insert(d[2][i]);
	}  
	map<int, int> m;
	for(auto x: s) m[x] = tot++;
	fr(i, n){
		d[0][i] = m[d[0][i]];
		d[1][i] = m[d[1][i]];
		d[2][i] = m[d[2][i]];
	}

	fr(i, n){
		caras[d[0][i]].pb(i);
	}
	tot--;
}

vector<pii> adj[MAXN];
void read(){
	cin >> n >> e;
	fr(i, e){
		int u, v, w;
		cin >> u  >> v >> w;
		adj[u].pb({v, w});
		adj[v].pb({u, w});
	}
}

void dijk(int v){
	int pr[MAXN];
	fr(i, n) pr[i] = 0;
	pq<pii, vector<pii>, greater<pii> > fila;
	fila.push({0, v});

	while(true){
		int davez = -1;
		while(fila.size()){
			if(!pr[fila.top().s]){
				davez = fila.top().s;
				pr[davez] = 1;
				d[v][davez] = fila.top().f;
				fila.pop();
				break;
			}
			fila.pop();
		}
		if(davez == -1) break;
		for(auto x : adj[davez]){
			int w = x.s, u = x.f;
			if(!pr[u]){
				fila.push({d[v][davez] + w, u});
			}
		}
	}
}

int main(){
	fastio;
	read();
	fr(i, 3) {
		dijk(i);	
	}
	coordinateCompress();
	/*
	fr(i, n){
		cout << d[0][i] << " " << d[1][i] << " " << d[2][i] << endl;	
	}
	*/
	build(1, 1, tot);
	frr(i, tot) solve(i);
	cout << n - ans << endl;
}
