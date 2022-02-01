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
const ll llINF = 1e18 + 1;
const int MOD = 1e9+7;
int m,n;
pll pp[1000500], cc[1000500];

vector<pll> p, c;

void read(){
	cin >> n; m = n;

	fr(i,m) cin >> pp[i].snd;
	fr(i,m) pp[i].snd = -pp[i].snd;
	fr(i,m) pp[i].fst = i + 1;
	fr(i,n) cc[i].fst = i + 1;
	fr(i,n) cc[i].snd = -pp[i].snd;

}

void clean(){
	sort(pp, pp + m);
	ll mn = llINF;
	fr(i,m){
		if(pp[i].snd >= mn) continue;
		mn = pp[i].snd;
		p.pb(pp[i]);
	}

	sort(cc, cc + n);
	ll mx = -llINF;
	for(int i = n - 1; i>= 0; i--){
		if(cc[i].snd <= mx) continue;
		mx = cc[i].snd;
		c.pb(cc[i]);
	}
	reverse(all(c));
}

ll dq(int lp, int rp, int lc, int rc){
	if(lp > rp || lc > rc) return 0;
	//dbg(lp); dbg(rp); dbg(lc);dbg(rc); gnl;
	int mp = (lp + rp)/2;
	ll ans = -llINF;
	ll index = -1;
	for(int j = lc; j <= rc; j++){
		if(c[j].fst < p[mp].fst) continue;
		ll tent = (c[j].snd - p[mp].snd)*(c[j].fst - p[mp].fst);
		if(tent >= ans){
			ans = tent;
			index = j;
		}
	}

	if(index == -1){
		index = rc;
	}

	ans = max(ans, 0ll);

	ll a = dq(lp, mp - 1,lc, index);
	ll b = dq(mp + 1, rp, index, rc);

	ans = max(ans,a);
	ans = max(ans,b);
	return ans;
}

int main(){

	fastio;

	read();
	clean();

	for(auto x: p){
	//	cout << x.fst << ' ' << x.snd << endl;
	}
	//gnl;
	for(auto x: c){
	//	cout << x.fst << ' ' << x.snd << endl;
	}

	cout << dq(0, p.size() - 1, 0 ,c.size() - 1) << endl;

}
