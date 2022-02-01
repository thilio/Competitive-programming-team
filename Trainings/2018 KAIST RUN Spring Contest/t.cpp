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
const int MAXN = 3e5 + 10;

typedef pair<ll, ll> pll;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	ll n, l[MAXN], d[MAXN];
	vector<pll> v;
	
	cin>>n;

	fr(i, n){
		cin>>l[i]>>d[i];
		v.pb({l[i] + d[i], i});
	}

	sort(all(v));

	ll sz, hgt;
	priority_queue<ll> pq;

	sz = hgt = 0;

	for (auto x : v){
		int i;
		tie(ignore, i) = x;
	
		if (hgt <= l[i]){
			sz++;
			hgt += d[i];
			pq.push(d[i]);
		}
		else if (hgt - pq.top() <= l[i] and d[i] < pq.top()){
			hgt -= pq.top() - d[i];
			pq.pop();
			pq.push(d[i]);

		}
	}	

	cout<<sz<<endl;
}