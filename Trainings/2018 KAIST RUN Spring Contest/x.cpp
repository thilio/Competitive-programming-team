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
const int MAXN = 1e6 + 10;

typedef tuple<ll, ll, ll> tup;
typedef pair<ll, ll> pll;


ll n, m, k, freq[MAXN];
vector<pll> adj[MAXN], path[MAXN][2];

void dij(ll src){
	memset(freq, 0, sizeof freq);

	ll nm = min(src - 1, 1ll); // 0 ou 1
	priority_queue<tup, vector<tup>, greater<tup> > pq; 
	pq.push({0, src, src}); // dist, meio, vtx

	ll dst, meio, vtx;
	while (!pq.empty()){
		tie(dst, meio, vtx) = pq.top();
		pq.pop();

		if (meio != src and freq[vtx] >= 3)// já tenho o que eu preciso
			continue;
		if (meio != src){
			freq[vtx]++;
			path[vtx][nm].pb({dst, meio});
			continue; // nenhum caminho maior que 2
		}
		
		for (auto x : adj[vtx])
			if (freq[x.fst] <= 2 or vtx == src)
				pq.push({dst + x.snd, vtx, x.fst});
	}
}

ll combine(ll a, ll b){
	ll ans = llINF;
	ll ma, mb, da, db;
	for (int i = 0; i < (int)path[a][0].size(); i++)
		for (int j = 0; j < (int)path[b][1].size(); j++){
			tie(da, ma) = path[a][0][i];
			tie(db, mb) = path[b][1][j];
			if (ma != b and ma != n and mb != a and mb != 1 and ma != mb)
				ans = min(ans, da + db);
		}

	return ans;		
}


ll dst1[MAXN], dstn[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>n>>m>>k;

	if (k > n or k > m){
		cout<<-1<<endl;
		return 0;
	}

	ll a, b, w;
	fr(i, m){
		cin>>a>>b>>w;
		adj[a].pb({b, w});
		adj[b].pb({a, w});
	}

	ll ans = llINF;

	fill(dst1, dst1 + MAXN, llINF);
	fill(dstn, dstn + MAXN, llINF);

	for (auto x : adj[1])
		dst1[x.fst] = min(dst1[x.fst], x.snd);

	for (auto x : adj[n])
		dstn[x.fst] = min(dstn[x.fst], x.snd);

	if (k == 1){
		ans = dst1[n];
		goto fim;
	}
	if (k == 2){
		for (int v = 2; v < n; v++)
			ans = min(ans, dst1[v] + dstn[v]);
		goto fim;
	}
	if (k == 3){
		for (int v = 2; v < n; v++)
			for (auto x : adj[v])
				if (x.fst != 1 and x.fst != n)
					ans = min(ans, dst1[v] + x.snd + dstn[x.fst]);
		goto fim;
	}

	dij(1);
	dij(n);

	ans = llINF;

	if (k == 4){
		for (int v = 2; v < n; v++)
			ans = min(ans, combine(v, v));
	}	
	else{
		for (int v = 2; v < n; v++)
			for (auto x : adj[v])
				if (x.fst != 1 and x.fst != n)
					ans = min(ans, combine(v, x.fst) + x.snd);
	}	

	fim: // goto	
		
	cout<<(ans == llINF ? -1 : ans)<<endl;	
}