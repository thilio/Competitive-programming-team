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

pii esq[MAXN], dir[MAXN];
int ebst[MAXN], ecom[MAXN], dbst[MAXN], dcom[MAXN];

void dfse(int v){
	ebst[v] = ecom[v] = 1; // só eu
	
	if (esq[v].fst != 0){ // tenho filho esquerdo
		dfse(esq[v].fst);
		ebst[v] = max(ebst[v], ebst[esq[v].fst]);
	}	
	if (esq[v].snd != 0){ // tenho filho central
		dfse(esq[v].snd); 
		ecom[v] = 1 + ecom[esq[v].snd];
		ebst[v] = max(ebst[v], ebst[esq[v].snd]);
	}

	ebst[v] = max(ebst[v], ecom[v]);	
}

void dfsd(int v){
	dbst[v] = dcom[v] = 1; // só eu
	
	if (dir[v].snd != 0){ // tenho filho direito
		dfsd(dir[v].snd);
		dbst[v] = max(dbst[v], dbst[dir[v].snd]);
	}	
	if (dir[v].fst != 0){ // tenho filho central
		dfsd(dir[v].fst);
		dcom[v] = 1 + dcom[dir[v].fst];
		dbst[v] = max(dbst[v], dbst[dir[v].fst]);
	}

	dbst[v] = max(dbst[v], dcom[v]);	
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m, a, b, c;

	cin>>n;
	fr(i, n){
		cin>>a>>b>>c;
		esq[a] = {b, c}; // esquerda centro
	}

	cin>>m;
	fr(i, m){
		cin>>a>>b>>c;
		dir[a] = {b, c}; // centro direito
	}

	int ce, cd;
	ce = cd = 0;

	int p = 1;
	while (p != 0){
		ce++;
		p = esq[p].snd;
	}

	p = 1;
	while (p != 0){
		cd++;
		p = dir[p].fst;
	}

	dfse(1);
	int me = ebst[1]; 
	dfsd(1);
	int md = dbst[1]; 

	cout<<m + n - max(min(ce, md), min(cd, me))<<endl;
}