#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define fr(i,n) 	for(int i=0;i<n;i++)
#define frr(i,n)	for(int i=1;i<=n;i++)

#define ms(x,i)	memset(x,i,sizeof(x))
#define endl '\n'
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

string s;
vector<int> N;
vector<vi> ans;

vector<int> uni = {1};


void subtract(vector<int> &a, vector<int> &b, vector<int> &c){ // return a - b in the vector c;
	while(b.size() < a.size()) b.pb(0);

	int n = a.size();
	c.resize(n);

	int cc = 0;
	for(int i = 0; i < a.size(); i++){
		cc += a[i] - b[i];
		if(cc < 0){
			c[i] = cc + 10;
			cc = -1;
		}
		else{
			c[i] = cc;
			cc = 0;
		}
	}	

	while(b.size() > 0 && b[b.size() - 1] == 0) b.pop_back();
	while(c.size() > 0 && c[c.size() - 1] == 0) c.pop_back();
}

void finish(){
	cout << ans.size() << endl;
	for(auto &x: ans){
		reverse(all(x));
		for(auto c: x) cout << c;
		gnl;
	}
}

void corner(){
	if(N.size() == 0) return;
	if(N.size() == 1){ ans.pb(N); return;}
	else{
		if(N[0] >= N[1]){
			vi aux;
			aux.pb(N[1]); aux.pb(N[1]);
			ans.pb(aux);
			if(N[0] == N[1]) return;
			aux.clear();
			aux.pb(N[0] - N[1]);
			ans.pb(aux);
		}
		else{
			vi aux;
			if(N[1] == 1 && N[0] == 0){
				aux.pb(9);
				ans.pb(aux);
				aux[0] = 1;
				ans.pb(aux);
				return;
			}
			aux.pb(N[1] - 1); aux.pb(N[1] - 1);
			ans.pb(aux);
			int k = 10 - (N[1] - 1) + N[0];
			aux.clear();
			if(k < 10){
				aux.pb(k);
			}
			else{
				aux.pb(9);
				ans.pb(aux);
				aux[0] = 1;
			}
			ans.pb(aux);
		}
	}
}

void solve(){
	ans.clear();
	cin >> s;
	reverse(all(s));
	N.clear();
	for(auto x: s) N.pb(x - '0');



	while(N.size() > 2){
		vector<int> b, c, d;
		if(N.size()%2 == 0){
			int k = N.size()/2;
			for(int i = k; i < N.size(); i++) b.pb(N[i]);
		
			subtract(b, uni, c);
			if(c.size() < b.size()){
				for(int l = c.size() - 1; l >= 0; l--) d.pb(c[l]);
				d.pb(9);
				for(int l = 0; l < c.size(); l++) d.pb(c[l]);
			}
			else{
				for(int l = c.size() - 1; l >= 0; l--) d.pb(c[l]);
				for(int l = 0; l < c.size(); l++) d.pb(c[l]);
			}
		}
		else{
			int k = N.size()/2;
			for(int i = k; i < N.size(); i++) b.pb(N[i]);
			subtract(b, uni, c);
			if(c.size() < b.size()){
				for(int l = c.size() - 1; l >= 0; l--) d.pb(c[l]);
				for(int l = 0; l < c.size(); l++) d.pb(c[l]);
			}
			else{
				for(int l = c.size() - 1; l >= 1; l--) d.pb(c[l]);
				for(int l = 0; l < c.size(); l++) d.pb(c[l]);
			}
		}
		vector<int> res;
		subtract(N, d, res);
		ans.pb(d);
		N = res;
	}

	corner();
	finish();
}

int main(){

	fastio;
	int T;
	cin >> T;
	while(T--){
		solve();
	}

}
