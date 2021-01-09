#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

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

int conv(char c){
	if (c == 'A')
		return 0;
	if ('2' <= c and  c <= '9')
		return c - '0' - 1;
	if (c == 'D')
		return 9;
	if (c == 'Q')
		return 10;
	if (c == 'J')
		return 11;
	return 12;
}

int n, k, turno;

int mao[14][14], joker, jokerr;

bool vence(int x){
	if (joker == x)
		return false;

	bool ok = 0; 
	int sum = 0;

	for (int i = 0; i < 14; i++){
		sum += mao[x][i];
		if (mao[x][i] == 4)
			ok = 1;
	}

	return (ok and sum == 4);
}

void passa_menor(int p1, int p2){
	int carta = 0, fq = 6;
	
	for (int i = 0; i < 14; i++)
		if (mao[p1][i] < fq and mao[p1][i] != 0){
			fq = mao[p1][i];
			carta = i;
		}

	mao[p1][carta]--;
	mao[p2][carta]++;
}


int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>k;

	joker = k - 1;
	jokerr = 1;

	string s;
	fr(i, n){
		cin>>s;
		for (auto x : s)
			mao[i][conv(x)]++;
	}

	fr(i, n) // vence no turno 0
		if (vence(i)){
			cout<<i + 1<<endl;
			return 0;
		}

	int p = k - 1; // começa o jogo

	while (true){
		if (vence(p)){ // vence antes da jogada
			cout<<p + 1<<endl;
			return 0;
		}
		if (vence((p + 1)%n)){ // proximo está vencendo
			cout<<(p + 1)%n + 1<<endl;
			return 0;
		}
		
		if (joker == p and jokerr == 0){
			jokerr = 1;
			joker = (p + 1)%n;
		}
		else
			passa_menor(p, (p + 1)%n);

		if (joker == p and jokerr == 1) // pode passar na proxima
			jokerr = 0;

		if (vence(p)){ // vence depois da jogada
			cout<<p + 1<<endl;
			return 0;
		}

		p = (p + 1) % n;
	}
}