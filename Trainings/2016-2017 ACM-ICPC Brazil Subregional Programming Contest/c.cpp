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

typedef pair<ll, vi> plv;
map<vi, long long int> dist;

void dij(vi src){
	priority_queue<plv, vector<plv>, greater<plv>> pq;
	pq.push({0, src});

	ll dst;
	vi vtx;
	while (!pq.empty()){
		tie(dst, vtx) = pq.top();
		pq.pop();

		if (dist.count(vtx) != 0)
			continue;
		dist[vtx] = dst;

		for (int i = 0; i < 4; i++){
			vi aux = vtx;
			swap(aux[i], aux[i + 4]);
			if (!dist.count(aux))
				pq.push({dst + aux[i] + aux[i + 4], aux});
		}
		for (int i = 0; i < 3; i++){
			vi aux = vtx;
			swap(aux[i], aux[i + 1]);
			if (!dist.count(aux))
				pq.push({dst + aux[i] + aux[i + 1], aux});	
		}
		for (int i = 4; i < 7; i++){
			vi aux = vtx;
			swap(aux[i], aux[i + 1]);
			if (!dist.count(aux))
				pq.push({dst + aux[i] + aux[i + 1], aux});	
		}
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	vi a, b;

	int x;
	fr(i, 8){
		cin>>x;
		a.pb(x);
	}
	fr(i, 8){
		cin>>x;
		b.pb(x);
	}

	dij(a);

	cout<<dist[b]<<endl;
}