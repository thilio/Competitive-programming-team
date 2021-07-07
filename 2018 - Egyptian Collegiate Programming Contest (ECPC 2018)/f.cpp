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
#define all(x)  x.begin(), x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

ll n, m, x, y;

void solve(){
	cin>>n>>m>>x>>y;

	if (n * (x + y) <= m){
		cout<<"0"<<endl; // media já é maior
		return;
	}

	if (y == 0){ // acabou
		cout<<-1<<endl;
		return;
	}

	cout<<(n * (x + y)) - m<<endl;
}

int32_t main(){
	freopen("mosalah.in", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	ll T;

	cin>>T;
	while (T--)
		solve();
}