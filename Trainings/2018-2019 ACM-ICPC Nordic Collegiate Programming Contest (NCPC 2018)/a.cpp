#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

#define endl '\n'
#define gnl cout << endl
#define chapa cout << "oi meu chapa" << endl
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e8 + 10;

typedef tuple<int, int, int> tup;
int n, d, hgt[MAXN];
vector<tup> v;

int32_t main(){
	fastio;
	cin>>n>>d;

	int l, w, h;
	fr(i, n){
		cin>>l>>w>>h;
		v.pb({w, h, l});
	}

	sort(all(v));
	reverse(all(v));

	memset(hgt, 0, sizeof h);

	int ans = 0;
	for (auto x : v){
		tie(w, h, l) = x;
		if (hgt[w] + l > d)
			ans++;
		frr(i, w - 1)
			if (i + w <= MAXN)
				hgt[i] = min(max(hgt[i], h + hgt[i + w]), d);
	}

	cout<<ans<<endl;
}