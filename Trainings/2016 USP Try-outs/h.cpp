#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(ll i = 0; i < n; i++)
#define frr(i, n) for(ll i = 1; i <= n; i++)
#define frm(i, n) for(ll i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<ll,ll> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007
#define MAXL 30
#define ROOT 1
#define INF 1000000000000000100

#define MAXP 3

ll n, m;
ll prime[MAXP] = {402653189, 805306457, 1610612741};
ll na[20], nb[20];

map<ll, pair<pii, ll>> maskA, maskB;
set<pair<pii, ll>> aux;

void imprime(ll m1, ll m2){
	cout << "Y\n";
	vector<ll> ret[2];
	ll i = 0;
	while(m1 > 0){
		if(m1 & 1) ret[0].pb(na[i]);
		m1/=2;
		i++;
	}
	i = 0;
	while(m2 > 0){
		if(m2 & 1) ret[1].pb(nb[i]);
		m2/=2;
		i++;
	}

	cout << ret[0].size() << " " << ret[1].size() << endl;
	fr(j, 2){
		for(auto x: ret[j]) cout << x << " ";
		cout << endl;
	}
}

ll getVal(ll mask, ll p, ll tp){
	ll ret = 1;
	ll i = 0;
	while(mask > 0){
		if(mask & 1) {
			if(tp == 0) ret = (ret * na[i])%prime[p];
			if(tp == 1) ret = (ret * nb[i])%prime[p];
		}
		mask/=2;
		i++;
	}

	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> m;
	fr(i, n) cin >> na[i];
	fr(i, m) cin >> nb[i]; 
	
	frr(i, (1 << n) - 1) maskA[i].f.f = getVal(i, 0, 0);
	frr(i, (1 << m) - 1) maskB[i].f.f = getVal(i, 0, 1);

	frr(i, (1 << n) - 1) maskA[i].f.s = getVal(i, 1, 0);
	frr(i, (1 << m) - 1) maskB[i].f.s = getVal(i, 1, 1);

	frr(i, (1 << n) - 1) maskA[i].s = getVal(i, 2, 0);
	frr(i, (1 << m) - 1) maskB[i].s = getVal(i, 2, 1);

	for(auto x: maskA) aux.insert(x.s);
	for(auto y: maskB){
		if(aux.find(y.s) != aux.end()){
			ll m1;
			for(auto x: maskA){
				if(x.s == y.s){
					m1 = x.f;
					break;
				}
			}

			imprime(m1, y.f);
			return 0;
		}
	}

	cout << "N\n";
}
