#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(int i = 0; i < n; i++)
#define frr(i, n) for(int i = 1; i <= n; i++)
#define frm(i, n) for(int i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 300010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

/*
	vertice, tipo, indice
*/
vector<pair<int, pii>> adj[MAXN];

/*

*/
int maxi[MAXN], mini[MAXN], pr[MAXN], tp[MAXN];
pii edge[MAXN];
int n, m, ini;

int dfsMaxi(int v){
	pr[v] = 1;
	int ret = 1;
	for(auto x: adj[v]){
		int to = x.f, tipo = x.s.f, ind = x.s.s;
		if(!pr[to]){
			if(tipo == 2 && edge[ind].f == to) maxi[ind] = 1;
			ret += dfsMaxi(to);
		}
	}
	return ret;
}

int dfsMini(int v){
	pr[v] = 1;
	int ret = 1;
	for(auto x: adj[v]){
		int to = x.f, tipo = x.s.f, ind = x.s.s;
		if(!pr[to]){
			if(tipo == 2){
				if(edge[ind].f == v) mini[ind] = 1;
			}
			else{
				ret += dfsMini(to);
			}
		}
	}
	return ret;
}

void read(){
	cin >> n >> m >> ini;

	frr(i, m){
		int tipo, u, v;
		cin >> tipo >> u >> v;
		edge[i] = {u, v};
		tp[i] = tipo;
		if(tipo == 1){
			adj[u].pb({v, {tipo, i}});
		}
		else{
			adj[u].pb({v, {tipo, i}});	
			adj[v].pb({u, {tipo, i}});	
		}
	}
}

int main(){
	fastio;
	read();
	cout << dfsMaxi(ini) << endl;
	frr(i, m){
		if(tp[i] == 1) continue;
		if(maxi[i]) cout << '-';
		else cout << '+';
	}
	cout << endl;

	frr(i, n) pr[i] = 0;
	cout << dfsMini(ini) << endl;
	frr(i, m){
		if(tp[i] == 1) continue;
		if(mini[i]) cout << '-';
		else cout << '+';
	}
	cout << endl;
}
