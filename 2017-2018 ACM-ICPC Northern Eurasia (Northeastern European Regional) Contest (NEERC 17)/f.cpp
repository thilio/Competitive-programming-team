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
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int sa, sb, rev; // sinal a, sinal b, revertido
int la, lb; // local a, local b
vector<tuple<int, int, int, int> > ans;

void add(int x1, int y1, int x2, int y2){ //vertical, horizontal
	x1 += la; x2 += la;
	y1 += lb; y2 += lb;
	if (rev){
		swap(x1, y2);
		swap(x2, y1);
	}
	ans.pb({sa*x1, sb*y1, sa*x2, sb*y2});
}

void solve(){
	ans.clear();
	int a, b, n;
	cin>>a>>b>>n;

	sa = (a == 0? 1 : a / max(1, abs(a)));
	sb = (b == 0? 1 : b / max(1, abs(b)));
	a = abs(a);
	b = abs(b);

	rev = 0;
	la = lb = 0; // começa no zero zero
	while (a > 0 or b > 0){
		if (a > b and a >= n){ // ambos grandes, b é maior
			rev = 1 - rev;
			swap(a, b); // diminuir o numero de casos
			swap(la, lb);
		}
		
		if (a >= n){ // menor dimensão é grande, vai na direção da maior
			add(n - 1, n - 1, 0, 0);
			b -= n; lb += n; // 1 unidade acima do ponto vertical
			a -= n - 1; la += n - 1;
		}	
		else { // vou matar uma dimensão
			add(a, n - 1, a - (n - 1), 0);
			b -= n; lb += n;
			la += a; a = 0;
		} // matou a e cobre de (0 -> n - 1) na vertical
	}

	// terminou um bloco abaixo
	if (a == 0 and b == 0)
		add(n - 1, n - 1, 0, 0);

	int d, f, g, h;
	cout<<ans.size()<<endl;
	for (auto x : ans){
		tie(d, f, g, h) = x;
		cout<<d<<' '<<f<<' '<<g<<' '<<h<<endl;
	}
}

int32_t main(){
	fastio;
	int T;
	cin>>T;
	while (T--)
		solve();
}