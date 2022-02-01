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
const int MAXN = 1e2 + 10;

int c, p;
map<string, int> cafe;

int s[MAXN], m[MAXN], l[MAXN];

void solve(){
	cafe.clear();

	cin>>c>>p;

	string v;
	fr(i, c){
		cin>>v;
		cafe[v] = i;
		cin>>s[i]>>m[i]>>l[i];
	}

	string t, u;
	int ans;
	fr(i, p){
		cin>>v>>t>>u;	
		ans = 100/p;
		if (t == "small")
			ans += s[cafe[u]];
		else if (t == "medium")
			ans += m[cafe[u]];
		else
			ans += l[cafe[u]];

		if (ans % 5 == 1)
			ans -= 1;
		else if (ans % 5 == 4)
			ans += 1;

		cout<<v<<' '<<ans<<endl; 
	}
}

int32_t main(){
	//freopen("coffee.in", "r", stdin);
	fastio;
	int T;
	cin>>T;
	while (T--)
		solve();
}