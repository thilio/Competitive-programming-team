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
const int MAXN = 1e3 + 10;

int n, m, q, k;

bitset<101> word[MAXN][11]; // frase, letra, posição
bitset<101> aux;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin>>n>>m>>q>>k;

	string s;
	fr(i, n){
		cin>>s;
		fr(j, m)
			word[i][s[j] - 'a'][j] = 1;
	}

	while (q--){
		fr(i, 11)
			word[n][i].reset(); // zera vetor
		
		cin>>s;	
		fr(j, m)
			word[n][s[j] - 'a'][j] = 1;

		int sum = 0;	
		fr(i, n){
			sum = 0;
			fr(j, 10){
				aux = word[n][j] & word[i][j];
				sum += (aux).count();
			}

			if (sum >= m - k)
				break;
		}	

		if (sum >= m - k)
			cout<<"S"<<endl;
		else
			cout<<"N"<<endl;
	}
}