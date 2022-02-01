#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(ll i = 0; i < n; i++)
#define frr(i, n) for(ll i = 1; i <= n; i++)
#define frm(i, n) for(ll i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<ll,ll> pii;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));
#define db cout << "Debug" << endl;
#define all(x) begin(x), end(x)
#define dbg(x)  cout << #x << " = " << x << endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define MAXN 100010
#define MOD 1000000007
#define MAXL 50
#define ROOT 1
#define INF 1000000000000000100
#define endl '\n';

ll exp(ll n, ll e, ll p){
    if(e == 0) return 1;
    ll ans = exp(n, e/2, p);

    ans = (ans*ans)%p;

    if(e%2 == 1) ans *= n;

    return (ans)%p;
}


ll n, p;
ll pwr[50][MAXN];
ll pwrGrande[50];

ll a[MAXN];
ll aux[50];
array<ll, 35> nd[4*MAXN];
array<ll, 35> nxt[4*MAXN];
bool lz[4*MAXN];

void build(ll i, ll l, ll r){
	fr(j, p) nxt[i][j] = j;
	lz[i] = 0;
	if(l == r) nd[i][a[l]]++;
	else if(l < r){
		ll m = (l + r)>>1;
		build(i<<1, l, m);
		build(i<<1|1, m + 1, r);
		fr(j, p) nd[i][j] = nd[i<<1][j] + nd[i<<1|1][j];
	}
}
void push(ll i, ll l, ll r){
	if(lz[i]){
		fr(j, p) aux[j] = 0;
		fr(j, p) aux[nxt[i][j]] += nd[i][j];
		fr(j, p) nd[i][j] = aux[j];
		
		if(l < r){
			lz[i<<1] = lz[i<<1|1] = 1; 
			fr(j, p){
				nxt[i<<1][j] = nxt[i][nxt[i<<1][j]];
				nxt[i<<1|1][j] = nxt[i][nxt[i<<1|1][j]];
			}
		}
		fr(j, p) nxt[i][j] = j;
		lz[i] = 0;
	}
}
void apply(ll i, ll op, ll k){
	if(op == 1){
		fr(j, p) 
			nxt[i][j] = (nxt[i][j] + k)%p;
	}
	else if(op == 2){
		fr(j, p)
			nxt[i][j] = (k*nxt[i][j])%p;
	}
	else{
		fr(j, p)
			nxt[i][j] = pwrGrande[nxt[i][j]];
	}
}
void update(ll i, ll l, ll r, ll ql, ll qr, ll op, ll k){
	if(l > r) return;
	push(i, l, r);
	if(ql <= l && r <= qr){
		apply(i, op, k);
		lz[i] = 1;
		push(i, l, r);
	}
	else if(ql > r || l > qr) return;
	else{
		ll m = (l + r)>>1;
		update(i<<1, l, m, ql, qr, op, k);
		update(i<<1|1, m + 1, r, ql, qr, op, k);
		fr(j, p) nd[i][j] = nd[i<<1][j] + nd[i<<1|1][j];
	}
}
ll query1(ll i, ll l, ll r, ll ql, ll qr, ll k){
	if(l > r) return 0;
	push(i, l, r);
	if(ql <= l && r <= qr){
		ll sum = 0;
		fr(j, p) sum += nd[i][j]*pwrGrande[j];
		return sum%p;
	}
	else if(ql > r || l > qr) return 0;
	else{
		ll m = (l + r)>>1;
		return query1(i<<1, l, m, ql, qr, k) + query1(i<<1|1, m + 1, r, ql, qr, k);
	}
}
ll query2(ll i, ll l, ll r, ll ql, ll qr){
	if(l > r) return 1;
	push(i, l, r);
	if(ql <= l && r <= qr){
		ll prod = 1;
		fr(j, p) prod = (prod*pwr[j][nd[i][j]])%p;
		return prod%p;
	}
	else if(ql > r || l > qr) return 1;
	else{
		ll m = (l + r)>>1;
		ll prod = 1;
		prod *= query2(i<<1, l, m, ql, qr);
		prod *= query2(i<<1|1, m + 1, r, ql, qr);
		return prod%p;
	}
}

int main(){
	scanf("%lld %lld", &n, &p);
	frr(i, n) scanf("%lld", &a[i]);
	frr(i, n) a[i] = a[i]%p;
	build(1, 1, n);

	fr(i, p) pwr[i][0] = 1;
	fr(i, p) frr(j, n) pwr[i][j] = (pwr[i][j-1]*i)%p;

	ll q;
	scanf("%lld", &q);
	while(q--){
		ll op, l, r, k;
		scanf("%lld %lld %lld %lld", &op, &l, &r, &k);
		fr(i, p) pwrGrande[i] = exp(i, k, p);
		if(op <= 3){
			update(1, 1, n, l, r, op, k);
		}
		else if(op == 4){
			printf("%lld\n", query1(1, 1, n, l, r, k) % p);
		}
		else{
			printf("%lld\n", query2(1, 1, n, l, r));
		}
	}
}