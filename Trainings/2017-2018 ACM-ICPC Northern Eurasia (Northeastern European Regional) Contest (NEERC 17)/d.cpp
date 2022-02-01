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

struct point{
	int cord[3];
};

vector<point> ans;
int perm[3];

ll a,b,c;
ll oa,ob,oc;

void print(){
	cout << ans.size() << endl;
	fr(i,ans.size()){
		fr(j,3){
			cout << ans[i].cord[perm[j]] << ' ';
		}
		gnl;
	}
}

void solve1(){
	point ini;
	fr(i,3) ini.cord[i] = 0;
	//ans.pb(ini);

	while(ini.cord[0] < b){
		ans.pb(ini);
		ini.cord[0]++;
	}

	ini.cord[0] = 0;

	while(ini.cord[1] < c - 1){
		ini.cord[1]++;
		ans.pb(ini);
	}

	//formei o retangulo vazio.

	ini.cord[0] = 1;
	ini.cord[1] = 1;

	int k = a - (b + c - 1);
	while(k > 0){
		while(ini.cord[1] <= c -1){
			ans.pb(ini);
			ini.cord[1]++;
			k--;
			if(k == 0) break;
		}
		ini.cord[0]++;
		ini.cord[1] = 1;
	}
}

void solve2(){
	point ini;
	fr(i,3) ini.cord[i] = 0;

	int j = 0;

	while(a != b -1){
		ans.pb(ini);
		ini.cord[1]++;
		c--;
		a--;
	}
	b--;

	ini.cord[0]++;

	while(c != 0){
		ans.pb(ini);
		ini.cord[0]++;
		ini.cord[1]++;
		c--;
		b--;
		a--;
	}


	ini.cord[1] = 0;
	ini.cord[2] = 0;

	while(a != 0){
		ans.pb(ini);
		ini.cord[0]++;
		a--;
	}
}

void find_perm(){
	if(oc <= ob && ob <= oa){
		perm[0] = 0;
		perm[1] = 1;
		perm[2] = 2;
		a = oa;
		b = ob;
		c = oc;
	}

	if(oc <= oa && oa <= ob){
		perm[0] = 0;
		perm[1] = 2;
		perm[2] = 1;
		a = ob;
		b = oa;
		c = oc;
	}

	if(ob <= oc && oc <= oa){
		perm[0] = 1;
		perm[1] = 0;
		perm[2] = 2;
		a = oa;
		b = oc;
		c = ob;
	}

	if(ob <= oa && oa <= oc){
		perm[0] = 2;
		perm[1] = 0;
		perm[2] = 1;
		a = oc;
		b = oa;
		c = ob;
	}

	if(oa <= oc && oc <= ob){
		perm[0] = 1;
		perm[1] = 2;
		perm[2] = 0;
		a = ob;
		b = oc;
		c = oa;
	}

	if(oa <= ob && ob <= oc){
		perm[0] = 2;
		perm[1] = 1;
		perm[2] = 0;
		a = oc;
		b = ob;
		c = oa;
	}

}

int main(){

	fastio;

	cin >> oa >> ob >> oc;
	find_perm();

	if(a > b*c){
		cout << -1 << endl;
		return 0;
	}

	if(a >= b + c - 1)
		solve1();
	else 
		solve2();

	print();



}
