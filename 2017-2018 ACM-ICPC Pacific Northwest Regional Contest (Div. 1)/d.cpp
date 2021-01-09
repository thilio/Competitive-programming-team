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
//cout << setprecision(9)<<fixed;

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int n, in[MAXN], out[MAXN], pai[MAXN], clk = 1;
int up[MAXN];
vii adj[MAXN];

void dfs(int v){
	in[v] = clk++;

	for (auto x : adj[v]){
		if (x.fst != pai[v]){
			pai[x.fst] = v;
			dfs(x.fst);
		}
	}

	out[v] = clk++;
}


int32_t main(){
	fastio;
	cin>>n;

	int a, b, c;
	fr(i, n - 1){
		cin>>a>>b>>c;
		adj[a].pb({b, c});
		adj[b].pb({a, c});
	}

	pai[1] = 1;
	dfs(1);

	vi cor;
	int j, p, m;
	frr(i, n){
		for (auto &x : adj[i])
			swap(x.fst, x.snd);
		sort(all(adj[i]));
	
		m = adj[i].size();
		j = 0;
		while (j < m){
			cor.clear();
			p = j;
			while (p < m and adj[i][p].fst == adj[i][j].fst){
				cor.pb(adj[i][p].snd);
				p++;
			}
			j = p;

			if (cor.size() > 1){
				for (auto x : cor){
					if (x == pai[i]){
						up[0]++;
						up[in[i]]--;
						up[out[i]]++;
					}
					else{
						up[in[x]]++;
						up[out[x]]--;
					}
				}
			}
		}
	}

	frr(i, 2*n + 10){
		up[i] += up[i - 1];
	}

	vi ans;
	frr(i, n)
		if (up[in[i]] == 0)
			ans.pb(i);
	cout<<ans.size()<<endl;
	for (auto x : ans)
		cout<<x<<endl;	
}