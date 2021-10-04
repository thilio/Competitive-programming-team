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
const int MAXN = 1e6 + 10;
const int MAXV = 1e7 + 10;

int lp[MAXV];
vi pr;

void crivo(){
	for (int i = 2; i < MAXV; i++){
	    if (lp[i] == 0){
	        lp[i] = i;
	        pr.push_back(i);
	    }
	    for (int j = 0; j < (int)pr.size() and pr[j] <= lp[i] and i * pr[j] < MAXV; j++)
	        lp[i * pr[j]] = pr[j];
	}
}

int n, a[MAXN], lft[MAXN], rgt[MAXN];
vi comp[MAXV];

int ans[MAXN];

void solve(int l, int r, int p){
	if (l > r) return;

	int ql = l, qr = r;

	while (ql <= qr){
		if (lft[ql] <= l and r <= rgt[ql]){
			ans[ql] = p;
			solve(l, ql - 1, ql);
			solve(ql + 1, r, ql);
			return;
		}
		ql++;

		if (lft[qr] <= l and r <= rgt[qr]){
			ans[qr] = p;
			solve(l, qr - 1, qr);
			solve(qr + 1, r, qr);
			return;
		}
		qr--;
	}

	cout<<"impossible"<<endl;
	exit(0);
}


signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	crivo();

	cin>>n;

	frr(i, n)
		cin>>a[i];

	frr(i, n){
		int aux = a[i];

		while (aux > 1){
			int x = lp[aux];
			comp[x].pb(i);

			while (lp[aux] == x)
				aux /= x;
		}
	}	

	frr(i, n){
		int aux = a[i];

		lft[i] = 1;
		rgt[i] = n;

		while (aux > 1){
			int x = lp[aux];

			int p = (int)(lower_bound(all(comp[x]), i) - comp[x].begin());
			
			if (p > 0)
				lft[i] = max(lft[i], comp[x][p - 1] + 1);
			if (p + 1 < comp[x].size())	
				rgt[i] = min(rgt[i], comp[x][p + 1] - 1);
			
			while (lp[aux] == x)
				aux /= x;
		}
	}

	solve(1, n, 0);

	frr(i, n)
		cout<<ans[i]<<' ';
	gnl;
}