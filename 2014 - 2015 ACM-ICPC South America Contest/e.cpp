#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

int n, m;
int c[100100];
pii edge[100100];
vi aresta[100100];

bool existe[100100];

int id[100100], sz[100100], val[100100];

void clear(int i){
	for(auto x: aresta[i]){
		int u = edge[x].fst;
		int v = edge[x].snd;
		id[u] = u;
		id[v] = v;
		sz[u] = sz[v] = 1;
		val[u] = c[u];
		val[v] = c[v];
	}
}

int find(int i){
	if(i == id[i]) return i;
	return id[i] = find(id[i]);
}

int merge(int u, int v){
	u = find(u);
	v = find(v);
	if(u == v) return val[u];
	if(sz[u] > sz[v]) swap(u, v);
	id[u] = v;
	sz[v] += sz[u];
	val[v] = __gcd(val[v], val[u]);
	return val[v];
}

bool tent(int i){
	if(existe[i]) return true;
	for(auto x: aresta[i]){
		if(merge(edge[x].fst, edge[x].snd) == i) return true;
	}

	return false;
}

int main(){

	fastio;
	cin >> n >> m;

	frr(i, n) cin >> c[i];
	frr(i, n) existe[c[i]] = true;

	frr(i, m){
		cin >> edge[i].fst >> edge[i].snd;

		int val = __gcd(c[edge[i].fst], c[edge[i].snd]);

		for(int j = 1; j*j <= val; j++){
			if(val%j == 0){
				aresta[j].pb(i);
				if(val != j*j) aresta[val/j].pb(i);
			}
		}
	}

	frr(i, n){
		id[i] = i;
		sz[i] = 1;
		val[i] = c[i]; 
	}

	int ans =  0;

	frr(i, 100000){
		if(tent(i)) ans++;
		clear(i);
	}

	cout << ans << endl;



}
