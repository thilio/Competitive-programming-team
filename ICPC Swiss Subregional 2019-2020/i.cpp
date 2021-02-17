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

int maxval = 1e7, v[7];
ll s;
bool memo[10001000][7];

void pd(){
	for (int falta = 1; falta <= maxval; falta++){ // valor restante
		for (int i = 1; i <= 6; i++){ // todas as faces
			bool ok = 0;
			for (int j = 1; j <= 6; j++)
				if (j != i and i + j != 7){
					if (falta - v[j] <= 0 or !memo[falta - v[j]][j])
						ok = 1;
				} 
			memo[falta][i] = ok;	
		}
	}
}

map<int, int> ciclo;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int top;
	frr(i, 6)
		cin>>v[i];
	cin>>s>>top;

	s -= v[top];

	maxval = (int) min<ll>(maxval, s);

	pd();

	if (maxval == s){ // simulei tudo
		if (memo[s][top])
			cout<<"ADA"<<endl;
		else
			cout<<"BOB"<<endl;
		return 0;
	}

	// agora tenho que achar o circuito
	int msk = 0, tam = 0, ini = 0;
	for (int i = 1; i <= maxval; i++){
		int sum = 0, bit = 0;
		for (int j = 1; j <= 6; j++)
			sum += memo[i][j];

		if (sum == 6){
			bit = 4;
		}
		else if (sum > 0){
			if (memo[i][1] == 0)
				bit = 1;
			else if (memo[i][2] == 0)
				bit = 2;
			else
				bit = 3;	
		}

		msk /= 5;
		msk += bit * 1953125; // 5^9

		if (ciclo.count(msk)){
			ini = ciclo[msk];
			tam = i - ini;
			break;
		}
		ciclo[msk] = i;
	}

	s -= ini;

	s %= tam;
	s += ini;

	if (memo[s][top])
		cout<<"ADA"<<endl;
	else
		cout<<"BOB"<<endl;
}