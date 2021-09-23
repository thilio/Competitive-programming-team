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

signed main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, x;

	cin>>n;

	stack<pii> stk;

	fr(i, n){
		cin>>x;

		pii aux = {x, x};
		while (!stk.empty() and stk.top().snd > aux.fst){ // maior dele é maior que o meu menor, mistura
			pii a = stk.top();
			stk.pop();
			aux = {min(aux.fst, a.fst), max(aux.snd, a.snd)};
		}
		stk.push(aux);
	}

	cout<<stk.size()<<endl;
}