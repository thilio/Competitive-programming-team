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

int n, lst[MAXN], deg[MAXN], dist[MAXN];
vi adj[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n;

	frr(i, n){
		int k;
		cin>>k;
		fr(j, k){
			int x;
			cin>>x;

			if (lst[x] != 0){
				deg[i]++;
				adj[lst[x]].pb(i);
			}
			lst[x] = i;
		}
	}

	queue<int> fila;

	frr(i, n)
		if (deg[i] == 0)
			fila.push(i);

	int v;	
	while (!fila.empty()){
		v = fila.front();
		fila.pop();

		for (auto x : adj[v]){
			dist[x] = max(dist[x], dist[v] + 1);
			deg[x]--;
			if (deg[x] == 0)
				fila.push(x);
		}
	}	

	int ans = 1;
	frr(i, n)
		ans = max(ans, dist[i] + 1);

	cout<<ans<<endl;
}