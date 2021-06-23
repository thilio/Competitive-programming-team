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

const ll M1 = 1e9+7;
const ll M2 = 999998143;

const ll P1 = 2;
const ll P2 = 3;

ll inv1, inv2;

pll hsh[100100];
vi s[100100];

int tudo[1000100];
pll hash_tudo;

int n;

ll fast(ll b, ll e, ll m){
	if(e == 0) return 1;
	ll ans = fast(b, e/2, m);
	ans = (ans*ans)%m;
	if(e&1) ans = (ans*b)%m;
	return ans;
}

void pre(){
	for(int i = 0; i < n; i++){
		ll p1 = 1;
		ll p2 = 1;
		for(auto x: s[i]){
			if(x == 1){
				hsh[i].fst = (hsh[i].fst + p1)%M1;
				hsh[i].snd = (hsh[i].snd + p2)%M2;
			}
			p1 = (p1*P1)%M1;
			p2 = (p2*P2)%M2;
		}
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < s[i].size(); j++) tudo[j]^=s[i][j];
	}
	
	ll p1 = 1;
	ll p2 = 1;

	for(int i = 0; i < 1000000; i++){
		if(tudo[i] == 1){
			hash_tudo.fst = (hash_tudo.fst + p1)%M1;
			hash_tudo.snd = (hash_tudo.snd + p2)%M2;
		}
		p1 = (p1*P1)%M1;
		p2 = (p2*P2)%M2;
	}

	inv1 = fast(P1, M1 - 2, M1);
	inv2 = fast(P2, M2 - 2, M2);
}

void modify(int i){
	ll p1 = 1;
	ll p2 = 1;
	fr(j, s[i].size()){
		if(s[i][j] == 1){
			if(tudo[j] == 0){
				hash_tudo.fst = (hash_tudo.fst + p1)%M1;
				hash_tudo.snd = (hash_tudo.snd + p2)%M2; 
			}
			if(tudo[j] == 1){
				hash_tudo.fst = (M1 + hash_tudo.fst - p1)%M1;
				hash_tudo.snd = (M2 + hash_tudo.snd - p2)%M2;	
			}
			tudo[j] = 1 - tudo[j];
		}
		p1 = (p1*P1)%M1;
		p2 = (p2*P2)%M2;
	}
}

int tent(int i){
	modify(i);

	pll at = hash_tudo;
	pll tent = hsh[i];

	int ans = 0;

	ll p1 = 1;
	ll p2 = 1; 

	for(int j = 0; j < s[i].size() - 1; j++){
		if(s[i][j] == 1){
			if(tudo[j] == 0){
				at.fst = (at.fst + p1)%M1;
				at.snd = (at.snd + p2)%M2; 
			}
			if(tudo[j] == 1){
				at.fst = (M1 + at.fst - p1)%M1;
				at.snd = (M2 + at.snd - p2)%M2;	
			}

			tent.fst = (M1 + tent.fst - 1)%M1;
			tent.snd = (M2 + tent.snd - 1)%M2;
		}

		tent.fst = (tent.fst*inv1)%M1;
		tent.snd = (tent.snd*inv2)%M2;

		if(at.fst == tent.fst && at.snd == tent.snd) ans++;

		p1 = (p1*P1)%M1;
		p2 = (p2*P2)%M2;
	}

	modify(i);

	return ans;
}

int main(){

	fastio;

	cin >> n;

	fr(i, n){
		string t;
		cin >> t;

		for(auto x: t){
			if(x == '0') s[i].pb(0);
			else s[i].pb(1);
		}
	}

	pre();


	ll ans = 0;

	fr(i, n){
		ans += tent(i);
	}

	cout << ans << endl;



}
