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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
pii a, b;
pii muve[100100];
map<pii, bool> exist;
bool bob[300][300];
int n;

int ran(int N){
	return uniform_int_distribution<int>(1, N)(rng);
}

bool valid(pii xx){
	int i = xx.fst;
	int j = xx.snd;
	if(i < 1 || i > n || j < 1 || j > n) return false;
	return true;
}

pii soma(pii xx, pii yy){
	return {xx.fst + yy.fst, xx.snd + yy.snd};
}
pii sub(pii xx, pii yy){
	return {xx.fst - yy.fst, xx.snd - yy.snd};
}

bool a_wins(){
	fr(i, n){
		pii at = soma(a, muve[i]);
		if(!valid(at)) continue;
		if(exist[sub(b, at)] || at == b) return true;
	}
	return false;
}

void small_b(){

	for(int i = 0; i < n; i++){
		pii at = soma(b, muve[i]);
		if(!valid(at)) continue;
		bob[at.fst][at.snd] = true;
		for(int j = 0; j < n; j++){
			pii ata = soma(at, muve[j]);
			if(valid(ata)) bob[ata.fst][ata.snd] = true;
		}
	}

	pii save = {0, 0};

	frr(i, n){
		frr(j, n){
			if(!bob[i][j] && b != mp(i, j)) save = {i, j};
		}
	}

	if(save.fst == 0) cout << "Bob wins" << endl;
	else cout << "tie " << save.fst << ' ' << save.snd << endl;
}

bool b_wins(pii x){
	fr(i, n){
		pii at = soma(b, muve[i]);
		if(!valid(at)) continue;
		if(exist[sub(x, at)]|| x == at) return true;
	}
	return false;
}

void big_b(){
	pii x;
	pii save = {0, 0}; 
	frr(i, 50){
		x.fst = ran(n);
		x.snd = ran(n);
		if(!b_wins(x)) save = x;
	}
	assert(save.fst != 0);
	cout << "tie " << save.fst << ' ' << save.snd << endl;
}

int main(){

	fastio;

	cin >> n;

	cin >> a.fst >> a.snd >> b.fst >> b.snd;

	fr(i, n) cin >> muve[i].fst >> muve[i].snd;
	fr(i, n) exist[muve[i]] = true;

	if(a_wins()) cout << "Alice wins" << endl;
	else if(n <= 200) small_b();
	else big_b();

}
