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

int n, a[MAXN];
ll b, ans[MAXN];

map<int, int> crd;

vi pos[MAXN];

signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin>>n>>b;

	int zr = 0;

	fr(i, n){
		cin>>a[i];
		if (a[i] == 0) zr = 1;

		crd[a[i]];
	}

	int cnt = 1 - zr;

	for (auto &e : crd)
		e.snd = cnt++;

	fr(i, n){
		a[i] = crd[a[i]];
		pos[a[i]].pb(i);
	}


	for (int i = 1; i <= n; i++){
		for (auto p : pos[i]){
			ll aux = 1; // minimo
			int l = (p - 1 + n) % n;
			int r = (p + 1) % n;
	
			if (a[l] < a[p])
				aux = max(aux, ans[l] + 1);

			if (a[r] < a[p])
				aux = max(aux, ans[r] + 1);

			ans[p] = aux;
		}

	}

	fr(i, n)
		cout<<ans[i] * b<<(i < n - 1 ? ' ':endl);
}