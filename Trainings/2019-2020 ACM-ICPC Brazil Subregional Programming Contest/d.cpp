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

int n, k, pai[MAXN];

int hgt[MAXN], folha[MAXN];
vi adj[MAXN];

int dfs_dp(int v, int p){
	if (adj[v].size() == 1 and v != p){// é folha;
		folha[v] = v;
		return v;
	}	
	int lf = 1, nd;
	for (int x : adj[v])
		if (x != p){
			hgt[x] = hgt[v] + 1;
			nd = dfs_dp(x, v);
			
			if (hgt[nd] > hgt[lf]) // folha mais profunda da sub
				lf = nd;
		}

	folha[v] = lf;
	return lf;	
}

bool out[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>n>>k;

	pai[1] = 1;
	frr(v, n - 1){
		cin>>pai[v + 1];
		adj[v + 1].pb(pai[v + 1]);
		adj[pai[v + 1]].pb(v + 1);
	}

	hgt[1] = 0;
	dfs_dp(1, 1);

	priority_queue<pii> pq;

	pq.push({hgt[folha[1]] + 1, 1});

	int cnt = 0, ans = 0;

	int h, v;
	while (!pq.empty() and cnt < k){ // maior cadeia
		tie(h, v) = pq.top();
		pq.pop();

		cnt++;
		ans += h;

		v = folha[v];
		while (!out[v]){
			for (int x : adj[v])
				if (!out[x] and x != pai[v])
					pq.push({hgt[folha[x]] - hgt[x] + 1, x});
			out[v] = 1;
			v = pai[v];
		}			
	}

	cout<<ans<<endl;
}