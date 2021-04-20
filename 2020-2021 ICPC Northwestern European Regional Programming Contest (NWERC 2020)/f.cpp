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
const int MAXN = 1e5 + 10;

struct frac {
	ll top, bot, a, b;

	frac(ll _a, ll _b, ll _c, ll _d): top(_a), bot(_b), a(_c), b(_d) {}	

	inline bool operator<(const frac &p) const { 
		if (top * p.bot < p.top * bot)
			return true;
		if (top * p.bot > p.top * bot)
			return false;
		return a < p.a; 
	}
};

int esq[MAXN], dir[MAXN], saiu[MAXN];
pii v[MAXN];

frac get_frac(int a, int b){
		if (a < b)
			swap(a, b); // a tem maior coordenada inicial	

		ll top = v[a].fst - v[b].fst;
		ll bot = v[b].snd - v[a].snd;

		if (bot > 0){
			ll mdc  = __gcd(top, bot);	// dbg(q.size());
			top /= mdc;
			bot /= mdc;

			return frac(top, bot, a, b);
		}
		else{
			return frac(-1, -1, -1, -1);
		}
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n;

	cin>>n;

	ll a, b;
	frr(i, n){
		cin>>a>>b;
		v[i] = {a, b};
	}

	set<frac> q;

	fr(i, n + 10){
		dir[i] = i + 1;
		esq[i] = i - 1;
	}

	for (int i = 1; i < n; i++){
		frac f = get_frac(i, i + 1);
		if (f.top > 0)
			q.insert(f);
	}

	while (!q.empty()){
		frac f = *q.begin();
		q.erase(q.begin());

		int d = f.a;
		int l = f.b;

		saiu[l] = saiu[d] = 1;

		dir[esq[l]] = dir[d];
		esq[dir[d]] = esq[l];

		if (esq[l] > 0){
			frac f = get_frac(esq[l], l);
			if (f.top > 0)
				q.erase(q.find(f));
		}
		if (dir[d] <= n){
			frac f = get_frac(dir[d], d);
			if (f.top > 0)
				q.erase(q.find(f));
		}
		if (esq[l] > 0 and dir[d] <= n){
			frac f = get_frac(esq[l], dir[d]);
			if (f.top > 0)		
				q.insert(f);
		}
	
	}

	vi ans;
	frr(i, n)
		if (saiu[i] == 0)
			ans.pb(i);

	cout<<ans.size()<<endl;
	for (auto x : ans)
		cout<<x<<' ';
	gnl;	


}