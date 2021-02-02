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
const int MAXN = 1e5 + 10;

int n, m;
bool disj[1123][1123];
vi adj[1123];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	while (cin>>n){
		cin>>m;

		frr(i, n){
			adj[i].clear();
			frr(j, n)
				disj[i][j] = 0;
		}

		int a, b;
		fr(i, m){
			cin>>a>>b;
			adj[b].pb(a);
		}

		for (int v = 2; v <= n; v++){
			disj[v][1] = 1;
			disj[1][v] = 1;

			for (auto u : adj[v])
				for (int w = 1; w < v; w++)
					if (disj[u][w]){
						disj[v][w] = 1;
						disj[w][v] = 1;
					}
		}
		int ans = 0;
		
		frr(i, n)
			frr(j, n)
				ans += disj[i][j];
		cout<<ans/2<<endl;			
	}
}