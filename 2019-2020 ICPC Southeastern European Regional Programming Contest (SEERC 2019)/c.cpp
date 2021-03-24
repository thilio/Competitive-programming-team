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

int n;
int pos;
int b[3000];
int resp[3000];

vi B[3000];
vi Q[3000];

vi level[3000];

int query1(int p){
	cout << 1 << ' ' << p << endl;
	int x;
	cin >> x;
	return x;
}

void query2(vi &v, vi& resp){
	int sz = v.size();
	resp.clear();
	if(sz == 1) return;
	cout << 2 << ' ';
	cout << sz << ' ';
	for(auto x: v) cout << x << ' ';
	gnl;

	fr(i, (sz*(sz - 1))/2){
		int x;
		cin >> x;
		resp.pb(x);
	}
}

void corner(){
	vi v;
	frr(i,n){
		int x = query1(i);
		v.pb(x);
	}
	cout << 3 << ' ';
	for(auto x: v) cout << x << ' ';
	gnl;
	exit(0);
}

void find_pos(){
	vi v, resp;
	frr(i, n) v.pb(i);

	query2(v, resp);
	int M = *(max_element(all(resp)));
	
	int l = 1;
	int r = n;
	while(l <= r){
		v.clear();
		int m = (l + r)/2;
		frr(i, m) v.pb(i);
		query2(v, resp);

		int MM = *(max_element(all(resp)));
		if(MM == M){
			r = m - 1;
			pos = m;
		}
		else{
			l = m + 1;
		}
	}
}

void F(vi &Q, vi &B){
	B.clear();
	vi resp1, resp2;
	query2(Q, resp1);
	Q.push_back(pos);
	query2(Q, resp2);
	Q.pop_back();

	map<int, int> M2;

	for(auto x: resp2) M2[x]++;

	for(auto x: resp1){
		M2[x]--;
		if(M2[x] == 0) M2.erase(x);
	}

	for(auto x: M2) B.pb(x.fst);
}

void break_Q(int j, int depth){
	int sz = Q[j].size();
	if(sz == 1) return;

	for(int i = 0; i < sz/2 ; i++){
		Q[2*j].pb(Q[j][i]);
	}
	for(int i = sz/2; i < sz; i++){
		Q[2*j + 1].pb(Q[j][i]);
	}

	level[depth + 1].pb(2*j);
	level[depth + 1].pb(2*j + 1);

	break_Q(2*j, depth + 1);
	break_Q(2*j + 1, depth + 1);
}

void find_b(){
	frr(i,n){
		if(i != pos) Q[1].pb(i);
	}
	level[0].pb(1);
	
	break_Q(1, 0);

	F(Q[1], B[1]);

	for(int l = 0; level[l].size() > 0; l++){
		vi QQ;
		vi BB;
		for(auto x: level[l]){
			int sz = Q[x].size();
			if(sz == 1){
				b[Q[x][0]] = B[x][0];
			}
			else{
				for(int i = 0; i < sz/2; i++) QQ.pb(Q[x][i]);
			}
		}
		if(QQ.size() == 0) continue;
		F(QQ, BB);
		set<int> BBaux;
		for(auto x: BB) BBaux.insert(x);

		for(auto x: level[l]){
			for(auto y : B[x]){
				if(BBaux.find(y) == BBaux.end()) B[2*x + 1].pb(y);
				else B[2*x].pb(y);
			}
		}
	}
}

int main(){

	fastio;
	cin >> n;
	if(n <= 30) corner();

	find_pos();
	find_b();

	int outro;

	if(pos == 1) outro = 2;
	else outro = 1;

	bool maximo;

	int base = query1(pos);

	if(base > query1(outro)) maximo = true;
	else maximo = false;

	frr(i,n){
		if(maximo) resp[i] = base - b[i];
		else resp[i] = base + b[i];
	}

	cout << 3 << ' ';
	frr(i, n) cout << resp[i] << ' ';
	gnl;




}
