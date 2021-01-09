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
ll sz,n,q;
ll l,r;
ll ans;
ll v[100100],freq[1000100];

struct qry{
	int l;
	int r;
	int ind;

	bool operator < (const qry& x) const{
		if (l/sz == x.l/sz) return (r < x.r);
		return l < x.l;
	}
};
qry qq[200100];


void add(ll val){
	freq[val]++;
	if(freq[val] == 2) ans+= 2;
	if(freq[val] > 2) ans++;
}

void remove(ll val){
	freq[val]--;
	if(freq[val] == 1) ans -= 2;
	if(freq[val] >= 2) ans--;
}

ll query(int x,int y){
	while(r < y) add(v[++r]);
	while(l > x) add (v[--l]);
	while(r > y) remove(v[r--]);
	while(l < x) remove(v[l++]);
	return ans;
}

int main(){

	
	scanf("%lld",&n);
	sz = (int)floor(sqrt(n)); 
	frr(i,n) scanf("%lld",v + i);
	scanf("%lld",&q);
	fr(i,q){
		qry a;
		scanf("%d",&a.l);
		scanf("%d",&a.r);
		a.ind = i;
		qq[i]= a;
	}

	sort(qq,qq+q);
	int res[200100];
	fr(i,q){
		qry a = qq[i];
		res[a.ind] = query(a.l,a.r); 
	}

	fr(i,q) printf("%d\n",res[i]);





}
