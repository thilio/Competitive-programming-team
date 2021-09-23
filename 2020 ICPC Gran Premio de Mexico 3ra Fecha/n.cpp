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
const int MAXN = 3e6 + 10;

ll d, b, m, h[MAXN];
vector<ll> p;

ll testa(ll val){
	int n = 0;
	fr(i, b + 2)
		h[n++] = 0; // inicio

	fr(i, m)
		h[n++] = p[i] - (i + 1) * val;	

	fr(i, b + 2)
		h[n++] = d - (m + 1) * val; // caras antes do final e o final

	reverse(h, h + n);


	ll slope = 0, linear = 0;
	priority_queue< pair<ll, ll> > pq;

	for (int i = 0; i < n; i++){
		slope += 1; 
		linear -=  h[i];
		pq.push({h[i], 2});

		while (slope > 0){
			ll pnt, frq;
			tie(pnt, frq) = pq.top();
			pq.pop();
			ll aux = min(slope, frq);
			slope -= aux;
			frq -= aux;
			linear += pnt * aux;
			if (frq > 0)
				pq.push({pnt, frq});
		}
	}

	return linear;
}


signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>d>>b>>m;

	p.resize(m);

	fr(i, m)
		cin>>p[i];

	sort(all(p));

	ll ini = 0, fim = d, bst = d;

	while (ini <= fim){
		ll meio = (ini + fim)/2;

		if (testa(meio) <= b){
			bst = meio;
			fim = meio - 1;
		}
		else
			ini = meio + 1;
	}	

	cout<<bst<<endl;
}