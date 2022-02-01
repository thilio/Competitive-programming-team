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
const int MAXN = 1e5 + 10;

int n, hgt[MAXN], esq[MAXN], dir[MAXN];

int t[2 * MAXN];

void modify(int p, int value) {  // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = min(t[p], t[p^1]);
}

int query(int l, int r) {  // sum on interval [l, r)
  int res = INF;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = min(res, t[l++]);
    if (r&1) res = min(t[--r], res);
  }
  return res;
}

const int gap = 150000;

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	while (cin>>n){
		fr(i, n)
			cin>>hgt[i];

		set<pii> q;

		for (int i = 0; i < n; i++){
			auto it = q.lower_bound({hgt[i] + 1, -1}); // qualquer cara de altura estritamente maior
			if (it == q.end()){
				esq[i] = -1;
			}
			else{
				esq[i] = (*it).snd;
			}
			while (!q.empty() and (*q.begin()).fst <= hgt[i])
				q.erase(*q.begin());

			q.insert({hgt[i], i});
		}

		q.clear();	

		for (int i = n - 1; i >= 0; i--){
			auto it = q.lower_bound({hgt[i] + 1, -1}); // qualquer cara de altura estritamente maior
			if (it == q.end()){
				dir[i] = -1;
			}
			else{
				dir[i] = (*it).snd;
			}
			while (!q.empty() and (*q.begin()).fst <= hgt[i])
				q.erase(*q.begin());
			q.insert({hgt[i], i});
		}

		fr(i, n)
			modify(i, hgt[i]);

		vi ans;
		for (int i = 0; i < n; i++){
			int minl, minr;
			minl = minr = -INF;
			if (esq[i] != -1)
				minl = query(esq[i], i); // query aberta na direita, mas foda-se
			if (dir[i] != -1)
				minr = query(i, dir[i]);


			if (hgt[i] - gap >= minl and hgt[i] - gap >= minr){
				ans.pb(i + 1);
			}
		}

		for (int i = 0; i < ans.size(); i++)
			cout<<ans[i]<<(i + 1 == ans.size() ? '\n' : ' ');
	}
}