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

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 2e3 + 10;

int v[MAXN];

void solve(){
	int n;
	cin>>n;
	fr(i, n)
		cin>>v[i];
	sort(v, v + n);
	reverse(v, v + n);

	int ans = 0, at = 0;

	while (at < n){
		if (at + 5 < n and v[at] - v[at + 5] <= 1000){
			at += 6;
			ans++;
		}
		else
			at++;
	}
	cout<<ans<<endl;	
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("overcode.in", "r", stdin);
	int T;
	cin>>T;
	while (T--)
		solve();
}