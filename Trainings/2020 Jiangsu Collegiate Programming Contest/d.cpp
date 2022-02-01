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
const int MAXN = 1e6 + 100;


bool prime[MAXN]; // diz se um numero não é primo, no caso, 1 é primo

void crivo(){
	fr(i, MAXN) prime[i] = true;

	for (int i = 2; i < MAXN; i++) {
		if (prime[i] && (long long)i * i < MAXN) {
			for (int j = i * i; j < MAXN; j += i)
				prime[j] = false;
		}
	}
}

int memo[MAXN], sumprime[MAXN];
vi rodada[MAXN];

// O JOGO DEMORA 80 TURNOS

int tipoa(int n, int k){
	int pos = 0;

	for (int i = 1; i < memo[k]; i++){ // soma geral que veio antes
		auto it = lower_bound(all(rodada[i]), n);
		// sai antes, tem alguem menor que n

		if (it == rodada[i].end())
			it--;
		if (*it > n) it--;
		pos += (int)(it - rodada[i].begin()) + 1;

	}

	auto it = lower_bound(all(rodada[memo[k]]), k); // sei que k está aqui
	pos += (int)(it - rodada[memo[k]].begin()) + 1;

	return pos;
}

int tipob(int n, int k){
	int pos = 0, aux;

	frr(i, 80){ // sei que não demora mais que isso
		auto it = lower_bound(all(rodada[i]), n);

		// sai antes, tem alguem menor que n

		if (it == rodada[i].end())
			it--;

		if (*it > n) it--;
		aux = (int)(it - rodada[i].begin()) + 1;
		
		if (pos + aux >= k) // achei
			return rodada[i][k - pos - 1];
		pos += aux;
	}
	return -1;
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	crivo();

	frr(i, MAXN - 1){
		sumprime[i] = prime[i];
		sumprime[i] += sumprime[i - 1];
	}

	for (int i = 1; i < MAXN; i++){
		if (prime[i]){
			memo[i] = 1; // é primo, sai na primeira rodada
		}
		else
			memo[i] = memo[i - sumprime[i]] + 1;
		
		rodada[memo[i]].pb(i);
	}

	int q, t, n, k;

	cin>>q;
	while (q--){
		cin>>t>>n>>k;

		if (t == 1)
			cout<<tipoa(n, k)<<endl;
		else
			cout<<tipob(n, k)<<endl;
	}
}