#include "bits/stdc++.h"
using namespace std;

#define pb push_back
#define fst first
#define snd second

#define fr(i,n)     for (int i = 0; i < n; i++)
#define frr(i,n)    for (int i = 1; i <= n; i++)

//#define endl '\n'
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

ll l, c, n, freq[MAXN];

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin>>l>>c>>n;

	set< pair<ll, ll> > q;

	freq[1] = l;
	q.insert({l - 1, 1}); // fim, elemeto
	
	ll p, x, a, b, lim, val;
	while (n--){
		cin>>p>>x>>a>>b;

		ll s = freq[p];

		ll m1 = (a + s * s) % l;
		ll m2 = (a + (s + b) * (s + b)) % l;
		
		if (m1 > m2)
			swap(m1, m2);
		
		// cout<<"kkk "<<m1<<' '<<m2<<' '<<x<<endl;
		// dbg(n);
		
    	freq[x] += m2 - m1 + 1;

		// primeiro intervalo completamente contido, cc
		auto it = q.lower_bound({m1 - 1, -1}); 
		
		// if (it == q.end())
		// 	chapa;	

		if (m1 != 0 and (*it).fst != m1 - 1)
			q.insert({m1 - 1, (*it).snd});
	
		while ((q.lower_bound({m1, -1}) != q.end()) and (*q.lower_bound({m1, -1})).fst <= m2){
			auto itt = q.lower_bound({m1, -1});
			lim = (*itt).fst;
			val = (*itt).snd;
			// dbg(val);
			// dbg(lim - m1 + 1);
			freq[val] -= lim - m1 + 1;
			m1 = lim + 1;
			q.erase(itt);
		}

		if (q.lower_bound({m1, -1}) != q.end()) {
			auto itt = q.lower_bound({m1, -1});
			lim = (*itt).fst;
			val = (*itt).snd;
			freq[val] -= m2 - m1 + 1;
		}
		q.insert({m2, x});
	}

	ll ans = 0;
	fr(i, MAXN)
		ans = max(ans, freq[i]);

	cout<<ans<<endl;	
}