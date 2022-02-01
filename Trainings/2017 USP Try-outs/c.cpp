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
int n,m;
int sprime[500500]; //sprime[i] = smallest prime that divides i
int v[500500];
vi prime[500500]; // prime factorization of each element
vi divi[500500]; // divisors
int pr[500500]; // first number before i that it is coprime with i
vi L[500500]; // L[i] = indices j such that i divides v[j]; 

int seg[2000200];

void update(int node,int l,int r,int pos,int val){
	if(l > pos || pos > r) return;
	if(l == r){
		seg[node] = val;
		return;
	}
	int m = (l + r)/2;
	update(2*node,l,m,pos,val);
	update(2*node + 1,m+1,r,pos,val);
	seg[node] = max(seg[2*node], seg[2*node + 1]);
}
int query(int node,int l,int r,int a,int b){
	if(b < l || a > r) return -1;
	if(a <= l && r <= b) return seg[node];
	int m = (l + r)/2;
	int q1 = query(2*node,l,m,a,b);
	int q2 = query(2*node + 1,m + 1,r,a,b);
	return max(q1,q2);
}

void build_sprime(){
	sprime[1] = 1;
	for(int i = 2; i <= 500000;i++){
		if(sprime[i] == 0){
			sprime[i] = i;
			for(int j = i; j <= 500000; j+= i){
				if(sprime[j] == 0) sprime[j] = i;
			}
		}
	}
}

void go_simple(){ // remove duplicate prime factors
	frr(i,n){
		int at = v[i];
		while(at != 1){
			int x = sprime[at];
			prime[i].pb(x);
			while(at%x == 0) at /= x;
		}
		v[i] = 1;
		for(auto x: prime[i]) v[i] *= x;
	}

	frr(i,n){
		int k = prime[i].size();
		for(int mask = 0; mask < (1 << k); mask++){
			int divisor = 1;
			fr(j,k){
				if(mask&(1 << j)) divisor *= prime[i][j]; 
			}
			divi[i].pb(divisor);
		}
	}
}

int mult(int x,int i){
	auto it = lower_bound(all(L[x]),i);
	int q = (int)(L[x].end() - it);
	return q;
}

int ncop(int i, int j){
 	int k = prime[j].size();
 	int ans = 0;
 	for(int mask = 0; mask < (1 << k); mask++){
 		if(mask == 0) continue;
 		int divisor = divi[j][mask];
 		int q = mult(divisor, i);
 		if(__builtin_popcount(mask)%2) ans += q;
 		else ans -= q; 
 	}
 	return ans;
}

int main(){

	fastio;
	build_sprime();
	cin >> n >> m;
	frr(i,n) cin >> v[i];
	go_simple();

	frr(j,n){	
		int l = 1;
		int r = j - 1;
		int best = 0;
		while(l <= r){
			int m = (l + r)/2;
			if(ncop(m,j) < j - m){
				best = m;
				l = m + 1;
			}
			else{
				r = m - 1;
			}
		}
		pr[j] = best;	
		for(auto x: divi[j]) L[x].pb(j);
	}

	frr(i,n){
		update(1,1,n,i,pr[i]);
	}

	frr(i,m){
		int l,r;
		cin >> l >> r;
		if(query(1,1,n,l,r) >= l){
			cout << 'S' << endl;
		}
		else{
			cout << 'N' << endl;
		}
	}
}
