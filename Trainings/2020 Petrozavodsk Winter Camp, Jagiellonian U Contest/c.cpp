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
const int MAXN = 2e5 + 10;

ll n, d;
vector<ll> h;

ll calc(){
	ll slope = 0, linear = 0;
	priority_queue< pair<ll, ll> > pq;

	for (int i = 0; i < n; i++){
		slope += 1; 
		linear -= h[i];
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

void solve(){
	cin>>n>>d;
	
	h.clear();

	ll x;
	fr(i, n){
		cin>>x;
		h.pb(x);
	}

	frr(i, n + 1)
		h.pb(-i*d);	
	
	sort(all(h));
	
	n += n + 1;

	fr(i, n)
		h[i] -= i * d;

	cout<<calc()<<endl;	
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin>>T;
	while (T--)
		solve();
}