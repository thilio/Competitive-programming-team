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
const int MAXN = 1e3 + 10;

typedef pair<ll, ll> pll;

ll n, m, k;
ll ask[MAXN], rdy[MAXN], frm[MAXN];
ll dist[MAXN][MAXN];
vector<pll> adj[MAXN];

void dij(int src){
	frr(i, MAXN) dist[src][i] = -1;
	priority_queue<pll, vector<pll>, greater<pll> > pq;

	pq.push({0, src});
	ll vtx, dst;

	while (!pq.empty()){
		tie(dst, vtx) = pq.top();
		pq.pop();

		if (dist[src][vtx] != -1)
			continue;
		dist[src][vtx] = dst;
		
		for (auto x : adj[vtx])
			if (dist[src][x.fst] == -1)
				pq.push({dst + x.snd, x.fst});
	}
}

ll memo[MAXN]; // memo[i] tempo mais cedo que volta ao restaurante após entrega i

bool test(ll val){
	ll tme, dst, lim;

	memo[0] = 0; // carro sai do restaurante
	for (int i = 1; i <= k; i++){
		memo[i] = llINF;

		dst = dist[1][frm[i]]; // casa[i] -> restaurante
		lim = ask[i]; // praso mais apertado

		for (int j = i; j >= 1; j--){
			tme = max(memo[j - 1], rdy[i]) + dist[1][frm[j]]; // tempo até a priemira casa com todos os pedidos
			if (tme - lim <= val) // entrega dentro dos limites de tempo
				memo[i] = min(memo[i], tme + dst); // volta mais adiantada pro restaurante
			dst += dist[frm[j - 1]][frm[j]]; // casa[j - 1] -> (casa[j] -> ... -> casa[i]) -> restaurante
			lim = min(ask[j - 1], lim - dist[frm[j - 1]][frm[j]]);
			// atualiza o limite de tempo
			// sempre mantemos o limite mais apertado
			// podemos comparar a entrega só da primeira casa
			// pois se uma casa k do meio for a mais apertada ela será
			// mantida em lim - (dist[j - 1][j] + ...+ dist[k - 1][k]
		}
		
		if (memo[i] == llINF)
			return false;
	}

	return true;
}

int32_t main(){
	fastio;
	cin>>n>>m;

	int u, v, d;

	fr(i, m){
		cin>>u>>v>>d;
		adj[u].pb({v, d});
		adj[v].pb({u, d});
	}

	cin>>k;

	frr(i, k)
		cin>>ask[i]>>frm[i]>>rdy[i];
	
	frr(i, n)
		dij(i);

	ll ini, fim, meio, best;
	ini = 0;
	best = fim = 6e14;

	while (ini <= fim){
		meio = (ini + fim)/2;
		if (test(meio)){
			fim = meio - 1;
			best = meio;
		}
		else
			ini = meio + 1;
	}	

	cout<<best<<endl;
}
