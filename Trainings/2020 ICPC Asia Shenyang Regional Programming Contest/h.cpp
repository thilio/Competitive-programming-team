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
const int MAXN = 3e5 + 10;

typedef pair<ll, ll> pll;

ll n, m, r, d[550], k[550], c[550], sum[MAXN];

pll v[MAXN];

ll proximo[100010][510], dia[MAXN];

ll memo[MAXN];


ll calc(ll bk, ll id){
	ll valh = bk - sum[dia[bk] - 1]; // quantos ainda faltam hj, incluindo a atual
	ll p = proximo[dia[bk]][id]; // proximo dia limite

	if (p == dia[bk]) // acaba hj!!!
		return bk - min<ll>(valh, k[id]); // o mais longe que da
	
	ll aux = sum[dia[bk] - 1] - sum[p - 1] + valh;

	return bk - min<ll>(k[id], aux); // quantas ele pode pegar, quantas pode pegar no tempo
}

ll pd(){

	for (ll q = 1; q <= sum[m]; q++){
		memo[q] = memo[q - 1] + r; // pagar 1 só

		for (ll i = 1; i <= n; i++){
			ll nxt = calc(q, i);
			memo[q] = min(memo[q], memo[nxt] + c[i]); // pagar esse cartao e ir pro proximo
		}
	}

	return memo[sum[m]];
}


signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>n>>m>>r;

	frr(i, n)
		cin>>d[i]>>k[i]>>c[i];

	ll p, q;	
	frr(i, m){
		cin>>p>>q;
		v[i] = {p, q};
	}

	sort(v + 1, v + m + 1);

	frr(i, m)
		sum[i] = sum[i - 1] + v[i].snd;

	ll at = 0;	
	frr(i, m){
		fr(j, v[i].snd){
			at++;
			dia[at] = i; // essa soma acontece nesse id
		}
	}		

	frr(i, n){
		ll l = 1, r = 1;

		while (r <= m){
			r = max(r, l);
			while (r <= m and v[r].fst <= v[l].fst + d[i] - 1){
				proximo[r][i] = l;
				r++;
			}
			// saiu, proximo cara ta mto longe
			l++;
		}
	}


	cout<<pd()<<endl;
}