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

map<int, int> extr; // outro extremo
set<int> itv; // intervalo
int n, k, q;

void add_itv(int a, int b){
	extr[a] = b;
	extr[b] = a;
	itv.insert(b);
}

void add(int x){
	extr[x] = x; //caso de intervalo sozinho

	// checar vizinhanças de x
	bool viz = 0;
	if (x < n and extr.count(x + 1)){ // vizinho a direita, expandir
		int top = extr[x + 1];
		extr[top] = x; 
		extr[x] = top;
	
		if (top != x + 1)
			extr.erase(x + 1);
	
		viz = 1;
	}

	if (viz and x > 1 and extr.count(x - 1)){ // vizinho a esquerda, expandir
		itv.erase(x - 1); // apaga intervalo começando a esquerda
		int esq = extr[x - 1];

		extr[extr[x]] = esq;
		extr[esq] = extr[x];
		
		if (esq != x - 1)
			extr.erase(x - 1);

		extr.erase(x);
	}
	
	if (!viz and x > 1 and extr.count(x - 1)){
		itv.erase(x - 1);
		itv.insert(x);

		int esq = extr[x - 1];

		extr[x] = esq;
		extr[esq] = x;
		if (esq != x - 1)
			extr.erase(x - 1);
		viz = 1;
	}

	if (!viz){
		add_itv(x, x);
	}
}

void remove(int y){
	int top = *itv.lower_bound(y); // cara na direita

	if (top == y){ // sou ponta direita
		itv.erase(top);

		if (extr[top] != top)
			add_itv(extr[top], top - 1);
			
		extr.erase(top);
	}
	else if (extr[top] == y){ // ponta esquerda, intervalo maior que 1
		extr[top] = y + 1;
		extr[y + 1] = top;
		extr.erase(y);
	}
	else{ // nenhum dois dois, intervalo maior que 2
		int esq = extr[top];
	
		// intv na direita
		extr[top] = y + 1;
		extr[y + 1] = top;

		// itv na esquerda
		add_itv(esq, y - 1);
	}
}

void solve(){
	extr.clear();
	itv.clear();

	cin>>n>>k>>q;

	add_itv(k + 1, n);

	int x, y;
	while (q--){
		cin>>x>>y;
		
		add(x);
		remove(y);	

		cout<<itv.size()<<endl;
	}
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int T;
	cin>>T;

	frr(i, T){
		cout<<"Case "<<i<<":"<<endl;
		solve();
	}
}