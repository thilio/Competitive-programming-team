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

int n, l, r, a[MAXN];
int memo[MAXN]; 

bool test(int val){
	memo[0] = 0; // fim do maior intervalo que consigo subdividir corretamente
	int maior = -1; // posição do ultimo elemento >= val
	int ini = 0; // inicio do meu intervalo atual
	for (int i = 1; i <= n; i++){
		if (a[i] >= val) 
			maior = i;
		ini = min(maior, i - l + 1);
		if (ini > 0 and memo[ini - 1] >= i - r) // já há l elementos e o ultimo intervalo válido dista de r 
			memo[i] = i; // posso terminar intervalo aqui e subdividir corretamente os primeiros i elementos
		else
			memo[i] = memo[i - 1]; // não consigo subdividir corretamente os primeiros i, 
	}							   // salva a melhor resposta até agora
	
	return memo[n] == n; // subdividi corretamente os primeiros n?
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin>>n>>l>>r;
	frr(i, n)
		cin>>a[i];

	int mn, mx, meio, bst;	
	mn = bst = 1;
	mx = 1e9 + 1;

	while (mn <= mx){
		meio = (mn + mx)/2;
		if (test(meio)) 
			bst = meio, mn = meio + 1;
		else 
			mx = meio - 1;
	}
	
	cout<<bst<<endl;
}
