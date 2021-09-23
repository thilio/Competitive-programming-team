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
const int MAXN = 5e5 + 10;

int n;
vi t[MAXN];

set<int> q, has[MAXN];
set<pii> itv[MAXN];

map<int, int> crd, crd2;

ll a, cst, b[MAXN], load[MAXN], hold[MAXN], tot;


signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n;

	frr(i, n){
		int k;
		cin>>k;
	
		fr(j, k){
			int x;
			cin>>x;
			if (t[i].empty() or t[i].back() < x)
				t[i].pb(x);	
			crd[t[i].back()];
		}
		
		k = t[i].size();

		fr(j, k - 1){
			q.insert(t[i][j + 1] - t[i][j]);
			itv[i].insert({t[i][j + 1] - t[i][j], t[i][j + 1]});
			crd2[t[i][j + 1] - t[i][j]];
		}
	}

	cin>>a;

	for (ll i = 1; i <= n; i++){
		cin>>b[i];
		b[i] *= i;
	}


	ll cnt = 1;
	for (auto &e : crd) // comprime os inicios
		e.snd = cnt++;

	cnt = 1;
	for (auto &e : crd2) // comprime os intervalos
		e.snd = cnt++;

	frr(i, n) // player que tem o intervalo x
		fr(j, (int)(t[i].size()) - 1)
			has[crd2[t[i][j + 1] - t[i][j]]].insert(i);


	frr(i, n) // todos os loads, com persistencia 0
		for (auto x : t[i]){
			cst -= b[load[crd[x]]];
			load[crd[x]]++;
			cst += b[load[crd[x]]];
			cst += a; // mantenho por 1 seg
		}


	frr(i, n)
		tot += itv[i].size() + 1;	
	
	ll bst = cst;
	vector<ll> ans = {1};

	ll lst = 0;
	while (!q.empty()){ // anda todos os intervalos
		ll x = *q.begin();
		q.erase(q.begin());

		ll inc = x - lst;

		cst += tot * inc * a;

		for (auto y : has[crd2[x]]){ // tem o intervalo x
			while (!itv[y].empty() and (*itv[y].begin()).fst == x){
				ll tme;
				tie(ignore, tme) = *itv[y].begin();
				itv[y].erase(itv[y].begin());

				cst -= a;
				tot--;

				cst -= b[load[crd[tme]]];
				load[crd[tme]]--;
				cst += b[load[crd[tme]]];
			}
		}

		lst = x;

		if (cst < bst){
			ans = {x + 1};
			bst = cst;
		}
		else if (cst == bst)
			ans.pb({x + 1});

		lst = x;
	}	

	cout<<bst<<' '<<ans.size()<<endl;
	for (auto x : ans)
		cout<<x<<' ';
	gnl;
}