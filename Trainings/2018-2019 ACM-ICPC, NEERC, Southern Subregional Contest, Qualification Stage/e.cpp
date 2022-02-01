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

int n, ini[MAXN], fim[MAXN], v[MAXN], prv[MAXN], nxt[MAXN];

int alt[MAXN];

void ajust(int p){
	if (ini[v[p]] == p)
		ini[v[p]] = nxt[p];
	if (fim[v[p]] == p)
		fim[v[p]] = prv[p];
	nxt[prv[p]] = nxt[p];
	prv[nxt[p]] = prv[p];
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>n;

	frr(i, n)
		cin>>v[i];

	fr(i, MAXN){
		ini[i] = n + 1;
		fim[i] = 0; 
	}

	frr(i, n){
		ini[v[i]] = min(ini[v[i]], i); // extremo esq
		fim[v[i]] = max(fim[v[i]], i); // extremo dir
	}

	int paux[MAXN];
	
	memset(paux, 0, sizeof paux);
	
	for (int i = 1; i <= n; i++){ // anterior da mesma cor
		prv[i] = paux[v[i]];
		paux[v[i]] = i;
	}

	fr(i, MAXN) 
		paux[i] = n + 1;

	for (int i = n; i > 0; i--){ // posterior da mesma cor
		nxt[i] = paux[v[i]];
		paux[v[i]] = i;
	}

	int m, cor, a, b, p;

	cin>>m;

	while (m--){
		cin>>cor;
		if (fim[cor] == 0)
			continue;

		a = ini[cor];
		b = fim[cor];

		p = a;
		if (alt[p] == 1)
			p = nxt[p] + 1; 
		else
			alt[p++] = 1;
		
		while (p < b and p <= n){
			if (alt[p] == 0){
				alt[p] = 1;
				ajust(p);	
			}
			else{
				ajust(p);
				
				p = nxt[p];
				
				ajust(p);
				alt[p] = 1;
			}
			p++;
		}

		alt[b] = 1;
		nxt[a] = b;
		prv[b] = a;

	}
	for (int i = 1; i <= n; i++){
		if (!alt[i])
			cout<<v[i]<<' ';
		else{
			for (int j = i; j <= nxt[i]; j++)
				cout<<v[i]<<' ';
			i = nxt[i];
		}
	}
	gnl;
}