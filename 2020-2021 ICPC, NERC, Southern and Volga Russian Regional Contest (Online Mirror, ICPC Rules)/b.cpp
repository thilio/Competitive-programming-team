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

int n,q;
ll a[200200];
ll pre[200200];
ll len[200200];
ll qry[200200];
ll join[200200];

ll ans;
vector<ll> resp;

set<pii> S;

ll query(ll l, ll r){ // [l,r)
	return pre[r - 1] - pre[l - 1];
}

int main(){

	fastio;
	cin >> n >> q;

	frr(i,n){
		cin >> a[i];
	}

	frr(i,n) pre[i] = a[i] + pre[i - 1];

	frr(i,n){
		join[i] = a[i] - 1;
		len[i] = 1;
		if(i == n) join[i] = -1;
		S.insert(mp(join[i], i));
	}

	ans = 0;

	frr(i,q) cin >> qry[i];

	for(int i = q; i > 0; i--){
		ll at = qry[i];
		auto it = S.end();
		it--;
		
		while((*it).fst >= at){
			pii inter = (*it);
			int com = inter.snd;

			int fim = com + len[com];
			ans = max(ans, len[com] + len[fim] - 1);

			S.erase(mp(inter.fst, inter.snd));
			S.erase(mp(join[fim], fim));
			
			len[com] += len[fim];
			join[com] = (query(com, com + len[com]) - 1)/(len[com]);

			if(com + len[com] > n) join[com] = -1;

			S.insert(mp(join[com], com));

			it = S.end();
			it--;
		}

		resp.pb(ans);
	}

	reverse(all(resp));

	for(auto x: resp) cout << x << ' ';
	gnl;
}
