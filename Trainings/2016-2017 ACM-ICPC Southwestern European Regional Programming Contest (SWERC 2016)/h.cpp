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

typedef unsigned long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

int d, h;

map<vi, ll> memo;

vi v, a;

set<ll> ans;

void solve(int pos, int mx, int lft){
	ll val = 0;
	fr(i, d){
		if (v[i] > 0){
			a = v;
			a[i]--;
			sort(all(a));
			val += memo[a];
		}	
	}
	if (val == 0)
		val++;

	memo[v] = val;

	if (lft == 0)
		ans.insert(val);

	if (pos > 0){
		for (int i = 1; i <= min(lft, mx); i++){
			v[pos - 1] = i;
			solve(pos - 1, i, lft - i);
		}
		v[pos - 1] = 0;
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>d>>h;

	h--; // tudo indexado do zero

	v.resize(d, 0);

	for (int i = 0; i <= h; i++){
		v[d - 1] = i;
		solve(d - 1, i, h - i);
	}

	while (!ans.empty()){
		cout<<*ans.begin()<<endl;
		ans.erase(ans.begin());
	}

}