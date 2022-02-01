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
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)

#define dbg(x)  cout << #x << " = " << x << endl
#define all(x)  x.begin(),x.end()

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int INF = 0x3f3f3f3f;
const ll llINF = (long long)(1e18) + 100;   
const int MAXN = 1e5 + 10;

ll n, hgt[MAXN], lft[MAXN], rgt[MAXN], ans[MAXN];

ll pd(ll v){
	if (ans[v] != -1)
		return ans[v];
	ans[v] = 0;
	if (lft[v] != 0)
		ans[v] = max(ans[v], pd(lft[v]) + v - lft[v]);
	if (rgt[v] != n + 1)
		ans[v] = max(ans[v], pd(rgt[v]) + rgt[v] - v);
	return ans[v];
}

int32_t main(){
	fastio;

	cin>>n;
	frr(i, n)
		cin>>hgt[i];

	hgt[0] = hgt[n + 1] = INF;

	stack<pii> stk;

	int h, p;
	stk.push({hgt[0], 0});
	frr(i, n){ // left
		while (true){
			tie(h, p) = stk.top();

			if (hgt[i] > h)
				stk.pop();
			else{
				if (hgt[i] < h){
					lft[i] = p;
					stk.push({hgt[i], i});
				}
				else
					lft[i] = lft[p];
				break;
			}
		}	
	}
	while (!stk.empty()) 
		stk.pop();
	
	stk.push({hgt[n + 1], n + 1});
	for (int i = n; i > 0; i--){ // right
		while (true){
			tie(h, p) = stk.top();

			if (hgt[i] > h)
				stk.pop();
			else{
				if (hgt[i] < h){
					rgt[i] = p;
					stk.push({hgt[i], i});
				}
				else
					rgt[i] = rgt[p];
				break;
			}
		}	
	}

	memset(ans, -1, sizeof ans);
	frr(i, n)
		cout<<pd(i)<<' ';
	gnl;
}