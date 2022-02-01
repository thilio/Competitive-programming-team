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

int main(){

	fastio;
	freopen("icecream.in", "r", stdin);
	int T;
	cin >> T;
	while(T--){
		int n,k;
		cin >> n >> k;
		vector<pii> v;
		int aux1[100100];
		int aux2[100100];
		v.clear();
		fr(i,n){
			cin >> aux1[i];
		}
		fr(i,n) cin >> aux2[i];

		fr(i,n) v.pb({aux1[i],aux2[i]});

		sort(all(v));

		int mx = v[k-1].fst;
		vector<pll> w;
		w.clear();

		fr(i,n){
			if(v[i].fst <= mx) w.pb(mp(v[i].snd,v[i].fst));
		}

		sort(all(w));
		reverse(all(w));

		ll sum = 0;
		fr(i,k) sum += w[i].fst;

		cout <<mx << ' '<< sum << endl;
	}

}
