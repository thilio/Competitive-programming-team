#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define dbg(x)	cout << #x << " = " << x << endl
#define all(x)	x.begin(),x.end()

#define gnl cout << endl
#define olar cout << "olar" << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll,ll> pll;

const int INF = 0x3f3f3f3f;
const ll llINF = 0x3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

ll n,k;
int v[100];
bool memo[40][40][40][110][110];
pll ans = mp(INF,1);
pll dif = mp(INF,1);
ll sum;

void pd(){
	memo[0][0][0][0][0] = true;

	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= n; j++){
			for(int k = 0; k <= n; k++){
				for(int somaa = 0; somaa <= 100; somaa++){
					for(int somab = 0; somab <= 100; somab++){
						if(somaa >= v[i] && j >= 1) memo[i][j][k][somaa][somab] |= memo[i - 1][j - 1][k][somaa - v[i]][somab];
						if(somab >= v[i] && k >= 1) memo[i][j][k][somaa][somab] |= memo[i - 1][j][k - 1][somaa][somab - v[i]];
						memo[i][j][k][somaa][somab] |= memo[i - 1][j][k][somaa][somab];
					}
				}
			}
		}
	}

}

pll simp(pll a){
	ll g = __gcd(a.fst, a.snd);
	a.fst /= g;
	a.snd /= g;
	return a;
}

pll mult(pll a, ll x){
	a.fst *= x;
	return a;
}

pll soma(pll a,pll b){
	return simp(mp(a.fst*b.snd + b.fst*a.snd, b.snd*a.snd));
}

bool menor(pll a, pll b){
	return (a.fst*b.snd < a.snd*b.fst);
}

void tent(int a,int b,int somaa,int somab){
	int somac = sum - somaa - somab;
	int c = n - a - b;

	//if(somac <= 0 || c <= 0) return;

	pll aa = mp(somaa,a);
	pll bb = mp(somab,b);
	pll cc = mp(somac,c);

	pll tr = soma(aa, bb);
	tr = soma(tr,cc);

	tr.snd *= 3;
	tr = simp(tr);

	pll difat;
	if(tr.fst >= tr.snd*k){
		difat = soma(tr, mp(-k,1));
	}
	else{
		difat = soma(mp(k,1), mp(-tr.fst,tr.snd));
	}

	if(menor(difat,dif)){
		dif = difat;
		ans = tr;
	}
	else if (difat.fst*dif.snd == difat.snd*dif.fst){
		if(tr.fst*ans.snd < tr.snd*ans.fst){
			dif = difat;
			ans = tr;
		}
	}
}

int main(){

	fastio;

	cin >> n >> k;
	frr(i,n) cin >> v[i];
	frr(i,n) sum += v[i];

	pd();

	for(int j = 1; j <= n - 2; j++){
		for(int k = 1; k <= n - 1 - j; k++){
			for(int somaj = 1; somaj <= 100; somaj++){
				for(int somak = 1; somak <= 100; somak++){
					if(memo[n][j][k][somaj][somak]){
						tent(j,k,somaj,somak);
					}
				}
			}
		}
	}

	cout << ans.fst << '/' << ans.snd << endl;

}
