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
const int MAXN = 1e3 + 10;
const ll mxshare = 100000;


ll n, a[MAXN], buy[MAXN], sell[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n;

	fr(i, n)
		cin>>a[i];

	ll ans = 100;
	ll paper = 0;
	ll lst = 0;

	fr(i, n){
		if (paper == 0){ // preciso comprar
			if (i == 0 or a[i - 1] > a[i]){ // não comprei nada ou acabei de vender
				paper = min(ans/a[i], mxshare); // o maximo que da para comprar
				lst = paper * a[i]; // o quanto gastei na ultima compra
				ans -= lst;
			}
			else{ // acabei de vender e foi barato
				ans -= sell[i - 1] * a[i - 1]; // recupera os papeis que vendi
				sell[i] = sell[i - 1]; // vou vender hj
				ans += sell[i] * a[i];
			}
		}
		else{
			if (a[i - 1] > a[i]){ // comprei caro!! vou desfazer
				ans += lst;
				paper = min(ans/a[i], mxshare);
				lst = paper * a[i];
				ans -= lst;
			}
			else{ // vamo vender
				sell[i] = paper;
				ans += paper * a[i];
				paper = 0;
			}
		}
	}

	if (paper > 0) // não valeu a pena comprar
		ans += lst;
	
	cout<<ans<<endl;
}