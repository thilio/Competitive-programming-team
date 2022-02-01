#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

// #define endl '\n'
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
const int MAXN = 1e5 + 10;

string s;
int n;

pii dir[400];

int other(char c){
	if (c == 'U') return 'D';
	if (c == 'D') return 'U';
	if (c == 'L') return 'R';
	return 'L';
}

pii operator+(pii a, pii b){
	return make_pair(a.fst + b.fst, a.snd + b.snd);
}

pii operator-(pii a, pii b){
	return make_pair(a.fst - b.fst, a.snd - b.snd);
}

pii operator*(int a, pii b){
	return make_pair(a * b.fst, a * b.snd);
}

int sai[200][200]; // tenho Saida

int passo = 2, nest;
vii estou, bloco;
pii fim;

map<pii, int> cnt;


void solve(int par, int itr){ // em qual movimento eu to
	if (itr == n){ // terminei
		fim = estou[par];
		return;	
	}

	if (sai[par][s[itr]] != 0){ // cuidado, pode ter bloco
		pii nxt = estou[sai[par][s[itr]]] + dir[s[itr]];
		if (cnt[nxt] == 1){ // tem bloco, volta para posição
			solve(sai[par][s[itr]], itr + 1);
			return;
		}
	}

	// vai para posição nova e cria bloco

	pii agora = estou[par];

	sai[par][s[itr]] = nest;

	agora = agora + passo * dir[s[itr]];
	passo *= 2;
	estou.pb(agora);


	bloco.pb(agora + dir[s[itr]]); // bloco da chegada
	cnt[agora + dir[s[itr]]] = 1;
	sai[nest][other(s[itr])] = par; // voltando na mesma direção

	nest++;
	solve(nest - 1, itr + 1);
	return;
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	dir['U'] = {0, 1};
	dir['D'] = {0, -1};
	dir['L'] = {-1, 0};
	dir['R'] = {1, 0};

	cin>>s;

	n = s.size();

	if (n == 1){ // só um movimento
		cout<<-dir[s[0]].fst<<' '<<-dir[s[0]].snd<<endl;
		cout<<0<<endl;
		return 0;
	}

	bool ok = 0; 
	for (int i = 0; i < n - 1; i++)
		if (s[i] == s[i + 1]) // dois movimentos consecutivos iguais
			ok = 1;

	reverse(all(s));	
	if (n > 2 and s[0] == s[2] and s[0] == other(s[1]))
		ok = 1;	
	reverse(all(s));

	if (ok){
		cout<<"impossible"<<endl;
		return 0;
	}	
	

	estou.pb({0, 0});
	nest++;

	pii agora = make_pair(0, 0) + passo * dir[s[0]]; 
	estou.pb(agora);
	bloco.pb(agora + dir[s[0]]); // ----->()[]
	cnt[agora + dir[s[0]]] = 1;

	nest++;

	passo *= 2; // saltos em potencia de 2

	solve(1, 1);

	pii ini = -1 * fim;

	cout<<ini.fst<<' '<<ini.snd<<endl;
	cout<<bloco.size()<<endl;
	for (auto l : bloco){
		pii x = l - fim;
		cout<<x.fst<<' '<<x.snd<<endl;
	}
}