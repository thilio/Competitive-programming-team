#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int32_t main(){
	fastio;
	int n;
	cin>>n; // profundidade

	int dst, at, aux;

	at = 1;
	cout<<at<<endl;
	cin>>dst;

	while (dst){
		at = 2 * at;
		cout<<at<<endl;
		cin>>aux;

		if (aux > dst){ // fui pro lado errado da árvore 
			at++; // agora fui para 2k + 1
			dst--;	
		}
		else
			dst = aux;
	}

	cout<<"! "<<at<<endl;
}